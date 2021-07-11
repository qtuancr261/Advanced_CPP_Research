/*
 * Author: tuantq3
 * File: serverapp.cpp
 *
 * Created on 26/8/2019
 */
#include "serverapp.h"

ServerApp::ServerApp() {}

void ServerApp::initialize(Poco::Util::Application &self) {}

void ServerApp::uninitialize() {}

void ServerApp::reinitialize(Poco::Util::Application &selft) {}

void ServerApp::defineOptions(Poco::Util::OptionSet &options) {}

void ServerApp::handleOption(const std::string &name, const std::string &value) {}

int ServerApp::main(const std::vector<std::string> &args) {
    /* System call: fd = socket(domain, type, protocol)
     *
     * Socket domains:                                                       Address structure   Address format
     * - AF_UNIX:  same host:                                                sockaddr_un         pathname
     * - AF_INET:  hosts connected via an IPv4 network:                      sockaddr_in         32-bit ipv4 address + 16-bit port number
     * - AF_INET6: hosts connected via an IPv6 network:                      sockaddr_in6        128-bit ipv6 address + 16 bit port number
     * - ...
     * Socket types:
     * - SOCK_STREAM: reliable, bidirectional, byte-stream -> TCP
     * - SOCK_DGRAM: connectionless -> UDP
     * - ...
     * Socket protocol: specified as 0 (non-0 protocol value are used with some socket types)
     *
     *
     */
    int socketServer{socket(AF_INET, SOCK_STREAM, 0)};
    if (socketServer < 0) {
        std::cerr << "Couldn't create socket ";
        return EX_OSERR;
    }

    sockaddr_in serverInfo{};
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(2610);
    serverInfo.sin_addr.s_addr = INADDR_ANY;

    /* System call: bind(sockfd, struct sockaddr*, socklen_t)
     * - sockaddr* : structure specifying the address to which this sockfd is to be bound
     * type of structure passed depends on the socket domain: AF_INET -> sockaddr_in
     * ** struct sockaddr: generic socket address structure
     * {
     *    sa_family_t sa_family;   address family
     *    char        sa_data[14]; Socket address
     * }
     * - socklen_t : the size ofthe address structure
     */
    if (bind(socketServer, (sockaddr *)&serverInfo, sizeof(serverInfo)) < 0) {
        std::cerr << "Couldn't bind socket \n";
        return EX_OSERR;
    }
    /* System call: listen(sockfd, backlog)
     * passive socket
     * the socket is used to accept connections from other (active) socket
     *
     */
    if (listen(socketServer, MAX_PENDING_CONNECTION) < 0) {
        std::cerr << "Couldn't listen to socket \n";
        return EXIT_OSERR;
    }
    std::cout << "Waiting for incoming connection ......... \n";

    vector<unique_ptr<thread>> threads{};
    sockaddr_in clientInfo{};
    int clLen{sizeof(clientInfo)};
    int socketClient{};
    while (true) {
        /* System call: accept(sockfd, struct sockadd*, socklen_t*)
         * Return: new socket that is connected to the peer socket that call connect()
         * - socklen_t* : point to an int that must be initialized to the size of the buffer pointed by sockadd*
         * - sockadd* : point to address of the peer socket
         * => BOTH sockadd* and socklen_t* could be specified as NULL if you're not interested in the address of the peer socket
         * => of course we can revive this info later by using getpeername() system call
         */
        socketClient = accept(socketServer, (sockaddr *)&clientInfo, (socklen_t *)&clLen);
        if (socketClient < 0) {
            continue;
        }
        std::cout << "Incoming connection from address " << inet_ntoa(clientInfo.sin_addr) << " port " << ntohs(clientInfo.sin_port) << endl;
        // thread handleClient{&ServerApp::handleNewConnection, this, socketClient};
        threads.push_back(make_unique<thread>(&ServerApp::handleNewConnection, this, socketClient));
        if (threads.size() == MAX_PENDING_CONNECTION) {
            break;
        }
    }
    for (auto &threadHandle : threads) {
        threadHandle->join();
    }
    std::cout << "Close sever application \n";
    close(socketServer);
    return EX_OK;
}
const char *ServerApp::name() const { return SERVER_NAME; }

void ServerApp::handleNewConnection(int clientSocket) {
    /*
     * I/O on stream socket
     * ----------------     Kernel
     * ---------------- -> buffer -> ---------------
     * App A: sockfd -> [-----------] App B: sockfd
     * ---------------- <- buffer <- ---------------
     */
    string welcomeMsg{"Welcome to chat box ! Have a nive day"};
    // send(clientSocket, welcomeMsg.c_str(), welcomeMsg.size(), 0);
    MessageClientReqRegister req;
    shared_ptr<uint8_t[]> messageData{};
    size_t messageSize{};
    req.name = welcomeMsg;
    if (req.serialize(messageData, messageSize)) {
        cout << "Framsize " << req.frameSize << endl;
        send(clientSocket, messageData.get(), messageSize, 0);
    }

    close(clientSocket);
    std::cout << "Close connection ....... \n";
}
