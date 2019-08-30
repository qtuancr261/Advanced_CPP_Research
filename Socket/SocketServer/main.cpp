#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <thread>
#include "bufferwrapper.h"
#include "messages/MessageClientReqRegister.h"
#include "roomchat.h"
#include "serverapp.h"
using namespace std;
const int MAXSIZE{200000};

shared_ptr<RoomChat> publicRoom{make_shared<RoomChat>("public room")};
int fileFlag{2000};
vector<shared_ptr<RoomChat>> privateRooms;
void* handleNewClientConnection(void* client_socket) {
    int client_socketFD{*(int*)client_socket};
    // Welcome new client with a message
    char messageFromServer[]{"Welcome to chat box. Have a nice day ! \n"};
    // char replyMessageFromServer[]{"I got it"};
    send(client_socketFD, messageFromServer, strlen(messageFromServer), 0);
    // Begin receiving from client
    char messageFromClient[MAXSIZE]{};
    recv(client_socketFD, messageFromClient, MAXSIZE, 0);
    // client_info new_client{client_socketFD, QString(messageFromClient)};
    QString clientName(messageFromClient);
    clientName.append(" send: ");
    // new_client.userName.append(" send: ");
    // clients.push_back(new_client);
    // clientPtr newClient{make_unique<client>(client_socketFD, clientName)};
    // publicRoom.addAClientToRoom(move(newClient));
    clientPtr newClient{make_shared<client>(client_socketFD, clientName)};
    publicRoom->addAClientToRoom(newClient);
    newClient->setCurrentStayedRoom(publicRoom);
    while (recv(client_socketFD, messageFromClient, MAXSIZE, 0) > 0) {
        printf("From client: %s", messageFromClient);
        QString qmessageFromClient(messageFromClient);
        // if (qmessageFromClient.section(" ", 0, 0) == QString("<FILE>"))
        RoomChat::MessageType msgType{publicRoom->specifyMessageType(qmessageFromClient)};
        switch (msgType) {
            case RoomChat::MessageType::FileRequest:
                fileFlag = 1;
                break;
            case RoomChat::MessageType::CreateRoomRequest: {
                QString roomName(qmessageFromClient.section(" ", 1, 1));
                // Create a new private room as request
                shared_ptr<RoomChat> newPrivateRoom{make_shared<RoomChat>(roomName)};
                privateRooms.push_back(newPrivateRoom);
                newClient->exitCurrentStayedRoom();
                newClient->setCurrentStayedRoom(newPrivateRoom);
                newPrivateRoom->addAClientToRoom(newClient);
                // publicRoom.removeAClientHasID(client_socketFD);
                /*for (const auto& room : privateRooms)
                 */    //printf("Room request : %s - ", room.getName().toStdString().c_str());
                break;
            }
            case RoomChat::MessageType::SwitchRoomRequest: {
                QString roomName{qmessageFromClient.section(" ", 1, 1)};
                for (auto& room : privateRooms) {
                    if (room->getName() == roomName) {
                        newClient->exitCurrentStayedRoom();
                        newClient->setCurrentStayedRoom(room);
                        room->addAClientToRoom(newClient);
                        qDebug() << "Switch room successfully";
                    }
                }
                break;
            }
            default:
                break;
        }

        if (!newClient->getCurrentStayedRoom().expired()) {
            shared_ptr<RoomChat> currentRoom{newClient->getCurrentStayedRoom().lock()};
            for (auto& pairID_Client : currentRoom->getClientsInRoom()) {
                if (pairID_Client.second->getId() != client_socketFD) {
                    if (fileFlag != 0) send(pairID_Client.second->getId(), clientName.toStdString().data(), clientName.size(), 0);
                    send(pairID_Client.second->getId(), messageFromClient, MAXSIZE, 0);
                }
            }
            fileFlag--;
            // strcpy(messageFromClient, " ");
            memset(messageFromClient, 0, sizeof(messageFromClient));
        }
    }
    printf("Client disconnected\n");
    return 0;
}
int main() {
    BufferWrapper::serializeDeserializeNumber();
    BufferWrapper::serializeDeserializeString();
    MessageClientReqRegister::testSerializeDeserialize();
    try {
        ServerApp app;
        return app.run();
    } catch (Poco::Exception& exc) {
        std::cerr << exc.what();
    }
}
