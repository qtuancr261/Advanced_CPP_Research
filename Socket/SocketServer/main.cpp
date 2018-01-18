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
const int MAXSIZE{20000};
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
        //printf("data from client: %s", messageFromClient);
        cout << messageFromClient << endl;
        ofstream fileO{"testFile.zip", ios::out | ios::ate};
        if (fileO.is_open())
        {
            cout << "Ok - O" << endl;
            fileO.seekp(0, ios::beg);
            fileO.write(messageFromClient, 16199);
            fileO.close();
        }
        else
            cout << "error - O" ;
        for (auto iterClient_socketFD = begin(client_socketFDs); iterClient_socketFD != end(client_socketFDs); iterClient_socketFD++)
            if (*iterClient_socketFD != client_socketFD)
                send(*iterClient_socketFD, messageFromClient, MAXSIZE, 0);
        strcpy(messageFromClient, "");
    }
     cout << "Client disconnected" << endl;
}
// Create a socket server
int main(int argc, char *argv[])
{
    int socket_server{socket(AF_INET, SOCK_STREAM, 0)};
    if (socket_server == -1)
        cerr << "Couldn't create socket" << endl;
    sockaddr_in server{};
    server.sin_port = htons(2610);
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    if (bind(socket_server, (sockaddr*)(&server), sizeof(server)) < 0)
    {
        cerr << "bind failed";
        exit(1);
    }
    // listen
    listen(socket_server, 5);
    cout << "Waiting for incoming connection " << endl;
    sockaddr_in client{};
    int client_size{sizeof(sockaddr_in)};
    int client_socket{};
    while((client_socket = accept(socket_server, (sockaddr*)&client, (socklen_t*)&client_size)))
    {
        if (client_socket < 0)
        {
            cerr << "connection failed";
            exit(1);
        }
        cout << "connection accepted from client: adress " << inet_ntoa(client.sin_addr) << " port " << ntohs(client.sin_port) << " des " << client_socket << endl;
        pthread_t serverHandlerThread{};
        int* ptrClient_socket{new int{client_socket}};
        if (pthread_create(&serverHandlerThread, nullptr, handleNewClientConnection, (void*)ptrClient_socket) < 0)
        {
            cerr << "Cannot create a thread for new connection";
        }

        /*cout << "connection accepted from client: adress " << inet_ntoa(client.sin_addr) << " port " << ntohs(client.sin_port) << " des " << client_socket << endl;
        send(client_socket, messageFromServer, strlen(messageFromServer), 0);

        if(recv(client_socket, messageFromClient, 2000, 0) > 0)
            cout << "Received from client: " << endl;
        send(client_socket, messageFromClient, strlen(messageFromClient), 0);
        cout << messageFromClient << endl;
        recv(client_socket, messageFromClient, 2000, 0);
        send(client_socket, messageFromClient, strlen(messageFromClient), 0);
        cout << messageFromClient << endl;*/
    }
    //int new_socket{accept(socket_desciptor, (sockaddr*)&client, (socklen_t*)&client_size)};
    //cout << strlen(message) << endl;
    close(socket_server);
    return 0;
}
