#ifndef HTTP_SERVER
#define HTTP_SERVER

#include<string>
#include<sys/socket.h>
#include<arpa/inet.h>

namespace http {

class Server {
    
public:

    Server(std::string ip_addr, int port);
    ~Server();
    void startListen();

private:
    
    std::string m_ipaddress;
    int m_port;
    int m_socket;
    int m_newsocket;
    struct sockaddr_in m_sockaddress;
    unsigned int len_sockaddr;
    long m_incomingMessage;
    std::string m_serverMessage;

    int startServer();
    void closeServer();
    void acceptConnection(int &new_socket);
    std::string Response();
    void sendResponse();

};
}

#endif // !HTTP_SERVER
