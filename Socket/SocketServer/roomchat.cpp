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

RoomChat::MessageType RoomChat::specifyMessageType(const QString &message)
{
    QString header{message.section(" ", 0, 0)};
    if (header == QString("<FILE>"))
        return MessageType::FileRequest;
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
