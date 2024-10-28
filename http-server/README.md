
# Simple HTTP Server in C++

## Overview
This project is a simple HTTP server written in C++ using the Linux socket API. It demonstrates the basic steps required to create, bind, listen, accept connections, read requests, and write responses. This server is designed for learning purposes and aims to provide a clear and concise example of socket programming in C++.

## Prerequisites
- A Linux environment
- C++ compiler (g++)
- Basic knowledge of C++ and socket programming

## Features
- Create a socket
- Bind to a specific port
- Listen for incoming connections
- Accept incoming connections
- Read HTTP requests from clients
- Write HTTP responses to clients

## How It Works

- **Creating a Socket**: `socket(AF_INET, SOCK_STREAM, 0)`
- **Binding to a Port**: `bind(server_fd, (struct sockaddr *)&address, sizeof(address))`
- **Listening for Connections**: `listen(server_fd, 3)`
- **Accepting Connections**: `accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)`
- **Reading from the Socket**: `read(new_socket, buffer, 1024)`
- **Writing to the Socket**: `write(new_socket, response, strlen(response))`

## Acknowledgements
This project is inspired by various online tutorials and examples on socket programming in C++. Special thanks to the open-source community for providing valuable resources and guidance. Thanks to the article written by Osamudiamen Azamegbe, I understood and implemented this project [Showing Building an HTTP Server from Scratch in C](https://osasazamegbe.medium.com/showing-building-an-http-server-from-scratch-in-c-2da7c0db6cb7).
