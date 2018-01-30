#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <cstdio>
#include <list>
#include <QString>
#include <QtDebug>
#include <memory>
#include "roomchat.h"
using std::list;
using std::string;
using std::weak_ptr;
using std::shared_ptr;
using std::make_shared;
class RoomChat;
class client
{
private:
    int id;
    QString name;
    weak_ptr<RoomChat> currentStayedRoom;
public:
    client(int id, QString name = "noname");
    int getId() const;
    void setId(int value);
    QString getName() const;
    void setName(const QString &value);
    weak_ptr<RoomChat>& getCurrentStayedRoom();
    void setCurrentStayedRoom(const shared_ptr<RoomChat> &value);
    void exitCurrentStayedRoom();
    ~client();
};

#endif // CLIENT_H
