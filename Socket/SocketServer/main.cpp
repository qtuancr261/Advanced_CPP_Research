#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <cstring>
#include <iostream>
#include <list>
#include <cstdio>
#include <fstream>
using namespace std;
const int MAXSIZE{200000};
list<int> client_socketFDs;
void* handleNewClientConnection(void* client_socket)
{
    int client_socketFD{*(int*)client_socket};
    client_socketFDs.push_back(client_socketFD);
    // Welcome new client with a message
    char messageFromServer[]{"Welcome to chat box. Have a nice day ! \n"};
    //char replyMessageFromServer[]{"I got it"};
    send(client_socketFD, messageFromServer, strlen(messageFromServer), 0);
    // Begin receiving from client
    char messageFromClient[MAXSIZE]{};
    while(recv(client_socketFD, messageFromClient, MAXSIZE, 0) > 0)
    {
        printf("From client: %s \n", messageFromClient);
        for (auto iterClient_socketFD = begin(client_socketFDs); iterClient_socketFD != end(client_socketFDs); iterClient_socketFD++)
            if (*iterClient_socketFD != client_socketFD)
                send(*iterClient_socketFD, messageFromClient, MAXSIZE, 0);
        //strcpy(messageFromClient, " ");
        memset(messageFromClient, 0, sizeof(messageFromClient));
    }
    printf("Client disconnected\n");
}
int main(int argc, char *argv[])
{
    int socket_server{socket(AF_INET, SOCK_STREAM, 0)};
    if (socket_server == -1)
        printf("Couldn't create socket\n");
    sockaddr_in server{};
    server.sin_port = htons(2610);
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    if (bind(socket_server, (sockaddr*)(&server), sizeof(server)) < 0)
    {
        printf("bind failed\n");
        exit(1);
    }
    // listen
    listen(socket_server, 5);
    printf("Waiting for incoming connection \n");
    // accept new connection
    sockaddr_in client{};
    int client_size{sizeof(sockaddr_in)};
    int client_socket{};
    while((client_socket = accept(socket_server, (sockaddr*)&client, (socklen_t*)&client_size)))
    {
        if (client_socket < 0)
        {
            printf("connection failed\n");
            continue;
        }
        printf("connection accepted from client: adress %s port %d des %d \n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), client_socket);
        pthread_t serverHandlerThread{};
        int* ptrClient_socket{new int{client_socket}};
        if (pthread_create(&serverHandlerThread, nullptr, handleNewClientConnection, (void*)ptrClient_socket) < 0)
        {
            printf("Cannot create a thread for new connection");
        }
    }
    //int new_socket{accept(socket_desciptor, (sockaddr*)&client, (socklen_t*)&client_size)};
    //cout << strlen(message) << endl;
    close(socket_server);
    return 0;
}
