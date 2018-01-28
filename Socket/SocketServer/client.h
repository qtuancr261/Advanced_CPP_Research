#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <cstdio>
#include <list>
#include <QString>
#include "roomchat.h"
using std::list;
using std::string;

class RoomChat;
class client
{
private:
    int id;
    QString name;
public:
    client(int id, QString name = "noname");
    int getId() const;
    void setId(int value);
    QString getName() const;
    void setName(const QString &value);
};

#endif // CLIENT_H
