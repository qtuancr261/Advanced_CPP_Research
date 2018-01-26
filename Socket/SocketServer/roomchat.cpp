#include "roomchat.h"

QString RoomChat::getName() const
{
    return name;
}

void RoomChat::setName(const QString &value)
{
    name = value;
}

vector<clientPtr> &RoomChat::getClientsInRoom()
{
    return clientsInRoom;
}

void RoomChat::addAClientToRoom(clientPtr client)
{
    clientsInRoom.push_back(move(client));
}

clientPtr RoomChat::removeAClientHasID(int id)
{
    for (auto& client : clientsInRoom)
    {
        if (client->getId() == id)
        {
            clientPtr tempPtr{move(client)};
            clientsInRoom.at(clientsInRoom.size() - 1).swap(client);
            clientsInRoom.pop_back();
            return tempPtr;
        }
    }
}

RoomChat::MessageType RoomChat::specifyMessageType(const QString &message)
{
    QString header{message.section(" ", 0, 0)};
    if (header == QString("<FILE>"))
        return MessageType::FileRequest;
    if (header == QString("<CREATE_ROOM>"))
        return MessageType::CreateRoomRequest;
    if (header == QString("<EXIT>"))
        return MessageType::ExitRoomRequest;
    return
            MessageType::Normal;
}
RoomChat::RoomChat(QString defName)
    : name{defName}
{
    // default constructor
}
