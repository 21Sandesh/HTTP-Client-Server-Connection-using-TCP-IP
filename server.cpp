// server.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

const int PORT = 8080;
const char *HostIP = "192.168.1.7"; // IP Address of the server

// Function to read the content of the "data.txt" file
std::string readDataFromFile()
{
    std::ifstream file("data.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void printServerActivity(const std::string &activity)
{
    std::cout << "[Server] " << activity << std::endl;
}

void *handleClient(void *socket_desc)
{
    int client_socket = *((int *)socket_desc);

    // Read data from the client
    char buffer[1024] = {0};
    read(client_socket, buffer, sizeof(buffer));

    // Find the start of the actual data (ignoring system/browser headers)
    const char *dataStart = strstr(buffer, "Name:");

    // If "Name:" is found, proceed with storing the data
    if (dataStart != nullptr)
    {
        // Parse the received data
        std::istringstream iss(dataStart);
        std::string name, prn, division, assignments;
        std::getline(iss, name);
        std::getline(iss, prn);
        std::getline(iss, division);
        std::getline(iss, assignments);

        // Remove leading strings
        name.erase(0, 6);         // "Name: " has 6 characters
        prn.erase(0, 5);          // "PRN: " has 5 characters
        division.erase(0, 9);     // "Division: " has 9 characters
        assignments.erase(0, 13); // "Assignments: " has 13 characters

        // Append the formatted data to the "data.txt" file
        std::ofstream file("data.txt", std::ios::app);
        file << "Name: " << name << "\nPRN: " << prn << "\nDivision: " << division << "\nAssignments: " << assignments << "\n\n";
        file.close();

        // Print the received data to the server's terminal
        std::cout << "Received Data:\n"
                  << "Name: " << name << "\nPRN: " << prn << "\nDivision: " << division << "\nAssignments: " << assignments << "\n"
                  << std::endl;

        // Construct HTTP response
        std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nAccess-Control-Allow-Origin: *\r\n\r\nData received and stored.\n";
        write(client_socket, response.c_str(), response.size());

        // Fetch and send data from "data.txt" to the client separately
        std::string fileContent = readDataFromFile();
        write(client_socket, fileContent.c_str(), fileContent.size());

        // Wait for acknowledgment from the client
        char ackBuffer[1024] = {0};
        read(client_socket, ackBuffer, sizeof(ackBuffer));
        std::cout << "Client Acknowledgment Received! " << std::endl;
    }
    else
    {
        // If "Name:" is not found, respond with an error
        std::string response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\nAccess-Control-Allow-Origin: *\r\n\r\n";
        write(client_socket, response.c_str(), response.size());
    }

    // Fetch and send data from "data.txt" to the client
    std::string fileContent = readDataFromFile();
    write(client_socket, fileContent.c_str(), fileContent.size());

    close(client_socket);
    delete (int *)socket_desc;
    pthread_exit(NULL);
}

int main()
{
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pthread_t thread_id;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        std::cerr << "Error creating socket." << std::endl;
        return -1;
    }

    // Set up server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(HostIP); // Host IP
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cerr << "Error binding socket." << std::endl;
        close(server_socket);
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1)
    {
        std::cerr << "Error listening for connections." << std::endl;
        close(server_socket);
        return -1;
    }

    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(server_addr.sin_addr), ip, INET_ADDRSTRLEN);
    std::cout << "Server listening on IP Address: " << ip << ", Port " << PORT << "..." << std::endl;

    printServerActivity("Server started. Waiting for connections...");

    while (true)
    {
        // Accept a connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == -1)
        {
            std::cerr << "Error accepting connection." << std::endl;
            continue;
        }
        else{
            std::cout << "Connection Accepted." << std::endl;
        }

        // Create a new thread to handle the client
        int *new_socket = new int;
        *new_socket = client_socket;
        if (pthread_create(&thread_id, NULL, handleClient, (void *)new_socket) < 0)
        {
            std::cerr << "Error creating thread." << std::endl;
            delete new_socket;
            continue;
        }
    }

    // Close the server socket
    close(server_socket);

    return 0;
}
