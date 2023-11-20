# HTTP Client-Server Communication using TCP/IP

## Description

This project implements a simple HTTP client-server communication system using TCP/IP. The server, implemented in C++, handles incoming requests from different clients. It writes and stores the data in a file named "data.txt" and reads the content of the file to send data back to the HTTP client.

## Server Side

The server has the following functionalities:

- Handles incoming requests from HTTP clients.
- Writes and stores client data in the "data.txt" file.
- Reads the content of the file and sends it back to HTTP clients.

## Client Side

The client side consists of a web page with the following features:

- Input fields for Name (Text), PRN (Number), Division (Dropdown), and Assignments (Checkbox).
- Upon submitting the data, it is sent to the server.
- The server stores the data in the "data.txt" file.

## Usage

### Server

1. Compile and run the server code written in C++.
2. The server listens for incoming requests on a specified port.

### Client

1. Open the "index.html" file in a web browser.
2. Fill in the form fields with the required data.
3. Submit the form to send data to the server.
4. The server stores the data in "data.txt".
5. Refresh the web page to fetch and display the data in a tabular form.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/21Sandesh/http-client-server.git
