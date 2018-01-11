#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    int client_socket{socket(AF_INET, SOCK_STREAM, 0)};
    if (client_socket < 0)
    {
        cerr << "Couldn't create socket ";
        exit(EXIT_FAILURE);
    }
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(2610);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(client_socket, (sockaddr*)&server, sizeof(server)) < 0)
        cerr << "Connection Failed";
    else
        cout << "Connection Successfully " << endl;
    char messageFromServer[2000]{};
    if (recv(client_socket, messageFromServer, 2000, 0) > 0)
        cout << messageFromServer;
    char messageFromClient[2000]{};
    cin.getline(messageFromClient, 2000);
    send(client_socket, messageFromClient, strlen(messageFromClient), 0);
    return 0;
}
