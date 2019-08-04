#include <arpa/inet.h>  // for inet_addr() function
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const string welcomeMsg{"Hello client !"};
int createTCPSocketV4() { return socket(AF_INET, SOCK_STREAM, 0); }
int createTCPSocketV6() { return socket(AF_INET6, SOCK_STREAM, 0); }
int createUDPSocketV4() { return socket(AF_INET, SOCK_DGRAM, 0); }
int createUDPSocketV6() { return socket(AF_INET6, SOCK_DGRAM, 0); }

[[noreturn]] void establishBasicServer(uint16_t port) {
    int sock_server{createTCPSocketV4()};
    if (sock_server < 0) {
        cerr << "Couldn't create socket";
        exit(1);
    }

    // prepare server info (address + port)
    sockaddr_in serverInfo{};
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(port);
    serverInfo.sin_family = AF_INET;
    // bind the created socket to an address + port
    if (bind(sock_server, (sockaddr*)(&serverInfo), sizeof(serverInfo)) < 0) {
        cerr << "Couldn't bind server info to socket " << sock_server;
        exit(1);
    }

    if (listen(sock_server, 5) < 0) {
        cerr << "Couldn't listen to prepare incoming connection ";
        exit(1);
    }

    printf("\nWaiting for connection \n");

    sockaddr_in clientInfo{};
    int clientLen{sizeof(sockaddr_in)};
    int sock_client{};
    while (true) {
        sock_client = accept(sock_server, (sockaddr*)(&clientInfo), (socklen_t*)&clientLen);
        if (sock_client <= 0) {
            continue;
        }
        cout << "Incoming connection from address " << inet_ntoa(clientInfo.sin_addr) << " port " << ntohs(clientInfo.sin_port) << endl;
        write(sock_client, welcomeMsg.c_str(), welcomeMsg.size());
    }
}

[[noreturn]] void establishBasicClient(const char* host, uint16_t port) {
    int sock_client{createTCPSocketV4()};
    if (sock_client < 0) {
        cerr << "Couldn't create socket \n";
        exit(1);
    }

    sockaddr_in serverInfo{};
    serverInfo.sin_addr.s_addr = inet_addr(host);
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(port);
}
int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << endl;
    }

    establishBasicServer(2610);
    return 0;
}
