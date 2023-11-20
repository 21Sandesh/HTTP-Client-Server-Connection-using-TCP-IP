# HTTP Client-Server Communication using TCP/IP

## Description

This project demonstrates a simple HTTP client-server communication system using TCP/IP. The server, implemented in C++, creates sockets, establishes connections, and handles incoming requests from multiple clients. The server writes received data to a file named "data.txt" and reads the file's content to send data back to HTTP clients.

## Server Features

The server has the following functionalities:

- Socket Programming in C++
- Connection establishment and management
- Handling incoming requests and storing data in "data.txt"
- Reading data from "data.txt" and responding to HTTP clients

## Client Features

The client side consists of a web page with the following features:

- HTML-based client with a form for data input
- Fields: Name (Text), PRN (Number), Division (Dropdown - CS-A, CS-B, CS-C, CS-D), Assignments (Checkbox - 1, 2, 3)
- Submits data to the server for storage in "data.txt"
- Retrieves stored data from the server and displays it in a tabular form on the web page

## Project Structure

- Server - "server.cpp" C++ File for Server-side Implementation.
- Client - "index.html" HTML File for Client-side Interface.

### Server

1. Compile and run the server code written in C++.
2. The server listens for incoming requests on a specified port.

### Running the Server
1. In the Terminal use the Command - `g++ -std=c++11 -o server server.cpp -lboost_system -pthread`
   - server.cpp is the C++ File Name.
2. Then use the Command - `./server` (To Start the Server)

### Client

1. Open the "index.html" file in a web browser.
2. Fill in the form fields with the required data.
3. Submit the form to send data to the server.
4. The server stores the data in "data.txt".
5. Refresh the web page to fetch and display the data in a tabular form.

### Running the Client

- For VS Code - Open the "index.html" File and start the Live Server or Show Preview.
- For Browser - Simply open the "index.html" File in the Browser

## Note

- This code was Designed and Implemented on Linux (Manjaro Gnome) Operating System.
- C++ Libraries like "arpa/inet.h", "sys/socket.h" and "pthread.h" are not supported in Windows Operating System.
- To Run the Server in Windows, use Winsock, Winsock2 Libraries and make changes accordingly.
- You would need to disable the firewall for the Ports used to overcome the Errors.
- For Error Troubleshooting and Solving, keep an eye on the Browser's Console Window.

### Firewall 
1. Open Terminal
2. Check the status - sudo ufw status
3. Allow the Port - `sudo ufw allow PORT_NUMBER` (PORT_NUMBER = Port Server is using)
4. Allow incoming traffic on Port - `sudo pacman -S ufw`
5. Restart the firewall - `sudo ufw enable`
6. To check the Status - `sudo ufw status`

# License

This project is licensed under the MIT License - see the [License](https://github.com/21Sandesh/HTTP-Client-Server-Connection-using-TCP-IP/blob/main/LICENSE) file for details.
