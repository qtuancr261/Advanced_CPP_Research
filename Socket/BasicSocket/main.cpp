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

void establishBasicServer(uint16_t port) {
    int sock_server{createTCPSocketV4()};
    if (sock_server < 0) {
        printf("Couldn't create socket \n");
        exit(1);
    }

    // prepare server info (address + port)
    sockaddr_in serverInfo{};
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(port);
    serverInfo.sin_family = AF_INET;
    // bind the created socket to an address + port
    if (bind(sock_server, (sockaddr*)(&serverInfo), sizeof(serverInfo)) < 0) {
        printf("Couldn't bind server info to socket %d", sock_server);
        exit(1);
    }

    if (listen(sock_server, 5) < 0) {
        printf("Couldn't listen to prepare incoming connection ");
        exit(1);
    }

    printf("\nWaiting for connection \n");

    sockaddr_in clientInfo{};
    int clientLen{sizeof(sockaddr_in)};
    int sock_client{};
    while (true) {
        sock_client = accept(sock_server, (sockaddr*)(&clientInfo), (socklen_t*)(&clientLen));
        if (sock_client <= 0) {
            continue;
        }
        cout << "Incoming connection from address " << inet_ntoa(clientInfo.sin_addr) << " port " << ntohs(clientInfo.sin_port) << endl;
        write(sock_client, welcomeMsg.c_str(), welcomeMsg.size());
    }
}
int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << endl;
    }

    if (!establishBasicServer(2610)) {
        cerr << "Failed to establish server";
    } else {
        cout << "Establised server successfully ";
    }
    //        ;
    //    // Firstly, we must create a socket
    //    int socket_desc;
    //    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    //    // AF_INET stands for Address family IP ver 4
    //    // SOCK_STREAM means TCP protocol
    //    if (socket_desc == -1) {
    //        cout << "Cannot create socket" << endl;
    //        exit(1);
    //    }

    //    // Indicate a server with ip address and port number to connect
    //    sockaddr_in server;
    //    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    //    // server.sin_addr.s_addr = INADDR_ANY;
    //    server.sin_family = AF_INET;
    //    server.sin_port = htons(11007);

    //    if (bind(socket_desc, (sockaddr*)(&server), sizeof(server)) < 0) {
    //        cerr << "bind failed";
    //        exit(1);
    //    }
    // connect to a server
    //    if (connect(socket_desc, (sockaddr*)&server, sizeof(server)) < 0)
    //        cout << "Error" << endl;
    //    else
    //        cout << "Connected" << endl;

    //    // Send data over socket(message)
    //    char* message{"Welcome to POSIX socket lib"};
    //    if (send(socket_desc, message, strlen(message), 0) < 0)
    //        cout << "send function failed" << endl;
    //    else
    //        cout << "Data transfering successfully" << endl;

    //    // Receive data on socket
    //    char receivedMessage[2000]{};
    //    if (recv(socket_desc, receivedMessage, 2000, 0) < 0)
    //        cout << "recv function failed" << endl;
    //    else
    //        cout << "Data transfering successfully" << endl;
    //    cout << receivedMessage << endl;
    //    // Finally, we close socket
    //    close(socket_desc);
    return 0;
}
