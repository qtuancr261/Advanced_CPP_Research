#ifndef ROOMCHAT_H
#define ROOMCHAT_H
#include "client.h"
#include <memory>
#include <vector>
#include <utility>
using std::vector;
using std::unique_ptr;
using std::make_unique;
using clientPtr = unique_ptr<client>;
using std::move;
class RoomChat
{
private:
    QString name;
    vector<clientPtr> clientsInRoom;
public:
    RoomChat(QString defName);

    QString getName() const;
    void setName(const QString &value);
    vector<clientPtr>& getClientsInRoom();
    void addAClientToRoom(clientPtr client);
};

#endif // ROOMCHAT_H
