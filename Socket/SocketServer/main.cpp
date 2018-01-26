#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <cstring>
#include <iostream>
#include <list>
#include <fstream>
#include "roomchat.h"
using namespace std;
const int MAXSIZE{200000};

RoomChat publicRoom("public room");
int fileFlag{2000};
vector<RoomChat> privateRooms;
void* handleNewClientConnection(void* client_socket)
{
    int client_socketFD{*(int*)client_socket};
    // Welcome new client with a message
    char messageFromServer[]{"Welcome to chat box. Have a nice day ! \n"};
    //char replyMessageFromServer[]{"I got it"};
    send(client_socketFD, messageFromServer, strlen(messageFromServer), 0);
    // Begin receiving from client
    char messageFromClient[MAXSIZE]{};
    recv(client_socketFD, messageFromClient, MAXSIZE, 0);
    //client_info new_client{client_socketFD, QString(messageFromClient)};
    QString clientName(messageFromClient);
    clientName.append(" send: ");
    //new_client.userName.append(" send: ");
    //clients.push_back(new_client);
    //clientPtr newClient{make_unique<client>(client_socketFD, clientName)};
    //publicRoom.addAClientToRoom(move(newClient));
    publicRoom.addAClientToRoom(make_unique<client>(client_socketFD, clientName));
    while(recv(client_socketFD, messageFromClient, MAXSIZE, 0) > 0)
    {
        printf("From client: %s", messageFromClient);
        QString qmessageFromClient(messageFromClient);
        //if (qmessageFromClient.section(" ", 0, 0) == QString("<FILE>"))
        RoomChat::MessageType msgType{publicRoom.specifyMessageType(qmessageFromClient)};
        switch (msgType)
        {
        case RoomChat::MessageType::FileRequest:
            fileFlag = 1;
            break;
        case RoomChat::MessageType::CreateRoomRequest:
        {
            QString roomName(qmessageFromClient.section(" ", 1, 1));
            privateRooms.push_back(RoomChat(roomName));
            privateRooms.at(0).addAClientToRoom(publicRoom.removeAClientHasID(client_socketFD));
            //publicRoom.removeAClientHasID(client_socketFD);
            /*for (const auto& room : privateRooms)
            */    //printf("Room request : %s - ", room.getName().toStdString().c_str());
            break;
        }
        default:
            break;
        }
        //if (publicRoom.specifyMessageType(qmessageFromClient) == RoomChat::MessageType::FileRequest)
        //    fileFlag = 1;
        /*for (auto iterClient = clients.begin(); iterClient != clients.end(); iterClient++)
            if (iterClient->socketFD != client_socketFD)
            {
                if (fileFlag != 0)
                    send(iterClient->socketFD, new_client.userName.toStdString().data(), strlen(new_client.userName.toStdString().data()), 0);
                send((iterClient->socketFD), messageFromClient, MAXSIZE, 0);
            }*/
        for (int i{}; i < publicRoom.getClientsInRoom().size(); i++)
        {
            if (publicRoom.getClientsInRoom().at(i)->getId() != client_socketFD)
            {
                if (fileFlag != 0)
                    send(publicRoom.getClientsInRoom().at(i)->getId(), clientName.toStdString().data(), clientName.size(), 0);
                send(publicRoom.getClientsInRoom().at(i)->getId(), messageFromClient, MAXSIZE, 0);
            }
        }
        fileFlag--;
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
