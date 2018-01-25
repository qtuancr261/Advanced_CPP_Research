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

RoomChat::RoomChat(QString defName)
    : name{defName}
{
    // default constructor
}
