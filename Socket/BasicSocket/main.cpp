#include <arpa/inet.h>  // for inet_addr() function
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <iostream>
// Basic example for socket programming on linux
// Create a socket
// Connect to remote server
// Send some data
// Receive some data
using namespace std;
int main(int argc, char* argv[]) {
    // Firstly, we must create a socket
    int socket_desc;
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET stands for Address family IP ver 4
    // SOCK_STREAM means TCP protocol
    if (socket_desc == -1) {
        cout << "Cannot create socket" << endl;
        exit(1);
    }

    // Indicate a server with ip address and port number to connect
    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    // server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(11007);

    if (bind(socket_desc, (sockaddr*)(&server), sizeof(server)) < 0) {
        cerr << "bind failed";
        exit(1);
    }
    // connect to a server
    if (connect(socket_desc, (sockaddr*)&server, sizeof(server)) < 0)
        cout << "Error" << endl;
    else
        cout << "Connected" << endl;

    // Send data over socket(message)
    char* message{"Welcome to POSIX socket lib"};
    if (send(socket_desc, message, strlen(message), 0) < 0)
        cout << "send function failed" << endl;
    else
        cout << "Data transfering successfully" << endl;

    // Receive data on socket
    char receivedMessage[2000]{};
    if (recv(socket_desc, receivedMessage, 2000, 0) < 0)
        cout << "recv function failed" << endl;
    else
        cout << "Data transfering successfully" << endl;
    cout << receivedMessage << endl;
    // Finally, we close socket
    close(socket_desc);
    return 0;
}
