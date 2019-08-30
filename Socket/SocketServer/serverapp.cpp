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
    int socketServer{socket(AF_INET, SOCK_STREAM, 0)};
    if (socketServer == -1) {
        std::cerr << "Couldn't create socket ";
        return EX_OSERR;
    }
    sockaddr_in serverInfo{};
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(2610);
    serverInfo.sin_family = AF_INET;

    if (bind(socketServer, (sockaddr *)&serverInfo, sizeof(serverInfo)) < 0) {
        std::cerr << "Couldn't bind socket ";
        return EX_OSERR;
    }

    listen(socketServer, 5);
    std::cout << "Waiting for incoming connection ......... \n";

    vector<thread *> threads{};
    sockaddr_in clientInfo{};
    int clLen{sizeof(clientInfo)};
    int socketClient{};
    while (true) {
        socketClient = accept(socketServer, (sockaddr *)&clientInfo, (socklen_t *)&clLen);
        if (socketClient <= 0) {
            continue;
        }
        std::cout << "Incoming connection from address " << inet_ntoa(clientInfo.sin_addr) << " port " << ntohs(clientInfo.sin_port) << endl;
        thread handleClient{&ServerApp::handleNewConnection, this, socketClient};
        handleClient.join();
        // threads.push_back(&handleClient);
        break;
    }
    // for (thread *&threadHandle : threads) {
    //    threadHandle->join();
    //}
    std::cout << "Close sever application \n";
    close(socketServer);
    return EX_OK;
}

const char *ServerApp::name() const { return SERVER_NAME; }

void ServerApp::handleNewConnection(int clientSocket) {
    string welcomeMsg{"Welcome to chat box ! Have a nive day"};
    send(clientSocket, welcomeMsg.c_str(), welcomeMsg.size(), 0);
    // close(clientSocket);
    std::cout << "Close connection ....... \n";
}
