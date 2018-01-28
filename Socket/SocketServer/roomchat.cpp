#include "roomchat.h"

QString RoomChat::getName() const
{
    return name;
}

void RoomChat::setName(const QString &value)
{
    name = value;
}

map<int, clientPtr> &RoomChat::getClientsInRoom()
{
    return clientsInRoom;
}

void RoomChat::addAClientToRoom(clientPtr client)
{
    clientsInRoom.insert(make_pair(client->getId(), move(client)));
}

clientPtr RoomChat::removeAClientHasID(int id)
{
    clientPtr matchedClient{move(clientsInRoom.at(id))};
    clientsInRoom.erase(id);
    return matchedClient;
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
