#include"include/server.h"

#include<string>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<iostream>
#include<unistd.h>
#include<sstream>

namespace {

const int BUFFER_SIZE = 30720;

void log(const std::string &message ) {
    std::cout << "[]   Log: " << message << std::endl;
}
    
void exception(const std::string &exception, int errorcode) {
    std::cout << "{} Error: " << exception << std::endl;
    exit(errorcode);
}

}

namespace http {

Server::Server(std::string ip_addr, int port) : 
    m_ipaddress(ip_addr),
    m_port(port),
    m_socket(),
    m_newsocket(),
    m_sockaddress(),
    len_sockaddr(sizeof(m_sockaddress)),
    m_serverMessage(Response()) {

    m_sockaddress.sin_family = AF_INET;
    m_sockaddress.sin_port = htons(m_port);
    m_sockaddress.sin_addr.s_addr = inet_addr(m_ipaddress.c_str());

    if(startServer() != 0) {
        exception("Failed initialization", 1);
    }
}

Server::~Server() {
    closeServer();
}

int Server::startServer() {
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(m_socket < 0) {
        exception("Socket Initialization Falied", 2);
        return 1;
    }
    if(bind(m_socket,(sockaddr *) &m_sockaddress, len_sockaddr) < 0) {
        exception("Socket Binding Failed", 3);
        return 1;
    }
    log("Server Started.......");
    return 0;
}

void Server::closeServer() {
    close(m_socket);
    close(m_newsocket);
    exit(0);
}

void Server::startListen() {
    
    if(listen(m_socket, 20) < 0) {
        exception("Socket Listening Failed", 4);
    }

    log("Listening to Address: ");
    std::cout << "\t" << inet_ntoa(m_sockaddress.sin_addr) << std::endl;
    log("Port: ");
    std::cout << "\t" << ntohs(m_sockaddress.sin_port) << std::endl; 

    int data;

    while(true) {
        log("Waiting For New Connection...");
        acceptConnection(m_newsocket);

        char buffer[BUFFER_SIZE] = {0};
        data = read(m_newsocket, buffer, BUFFER_SIZE);
        if (data < 0) {
            exception("Failed to Read Data", 6);
        }
        log("Recieved request from client");

        sendResponse();
        close(m_newsocket);

    }
}

void Server::acceptConnection(int &new_socket) {
    new_socket = accept(m_socket, (sockaddr *) &m_sockaddress, &len_sockaddr);
    if (new_socket<0) {
        exception("Failed to Accept Connection", 5);
    }
}

std::string Server::Response() {
    
    std::string htmlFile = "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello, World! :) </p></body></html>";
    std::ostringstream ss;
    ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n"
           << htmlFile;

    return ss.str();
}

void Server::sendResponse() {
    long dataSent;
    dataSent = write(m_newsocket, m_serverMessage.c_str(), m_serverMessage.size());
    if(dataSent == m_serverMessage.size()) {
        log("Server Response Sent to Client");
    } 
    else {
        exception("Error Sending Response", 7);
    }
}
}
