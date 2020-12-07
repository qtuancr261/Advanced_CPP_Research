#include "client.h"
#include "roomchat.h"
weak_ptr<RoomChat> &client::getCurrentStayedRoom()
{
    return currentStayedRoom;
}

void client::setCurrentStayedRoom(const shared_ptr<RoomChat> &value)
{
    currentStayedRoom = value;
}

void client::exitCurrentStayedRoom()
{
    if (!currentStayedRoom.expired())
    {
        shared_ptr<RoomChat> currentRoom{currentStayedRoom.lock()};
        currentRoom->removeAClientHasID(id);
    }
    currentStayedRoom.reset();
}

client::~client()
{
    qDebug() << "A client has been deleted";
}

client::client(int id, QString name)
    : id{id}, name{name}
{
    // default constructor
}

int client::getId() const
{
    return id;
}

void client::setId(int value)
{
    id = value;
}

QString client::getName() const
{
    return name;
}

void client::setName(const QString &value)
{
    name = value;
}


