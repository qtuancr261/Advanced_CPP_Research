#ifndef ROOMCHAT_H
#define ROOMCHAT_H
#include "client.h"
#include <memory>
#include <vector>
#include <utility>
#include <map>
class client;
using std::vector;
using std::map;
using std::unique_ptr;
using std::pair;
using std::make_unique;
using std::make_pair;
using std::move;
using clientPtr = unique_ptr<client>;


class RoomChat
{
private:
    QString name;
    //vector<clientPtr> clientsInRoom;
    map<int, clientPtr> clientsInRoom;
public:
    enum class MessageType
    {
        Normal,
        FileRequest,
        SwitchRoomRequest,
        GetRoomsRequest,
        GetClientsInRoomRequest,
        CreateRoomRequest,
        ExitRoomRequest,
        InviteToRoomRequest,
        ConfirmAnInvitationRequest
    };
    RoomChat(QString defName);
    QString getName() const;
    void setName(const QString &value);
    map<int, clientPtr>& getClientsInRoom();
    void addAClientToRoom(clientPtr client);
    clientPtr removeAClientHasID(int id);
    MessageType specifyMessageType(const QString& message);
};

#endif // ROOMCHAT_H
