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

void RoomChat::addAClientToRoom(clientPtr &client)
{
    int fd{client->getId()};
    clientsInRoom.insert(make_pair(fd, client));
    //clientsInRoom.at(fd)->setCurrentStayedRoom(shared_ptr<RoomChat>(this));
}

void RoomChat::removeAClientHasID(int id)
{
    clientsInRoom.at(id).reset();
    clientsInRoom.erase(id);
}

RoomChat::MessageType RoomChat::specifyMessageType(const QString &message)
{
    QString header{message.section(" ", 0, 0)};
    if (header == QString("<FILE>"))
        return MessageType::FileRequest;
    if (header == QString("<CREATE_ROOM>"))
        return MessageType::CreateRoomRequest;
    if (header == QString("<JOIN_ROOM>"))
        return MessageType::SwitchRoomRequest;
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
