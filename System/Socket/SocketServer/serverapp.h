/*
 * Author: tuantq3
 * File: serverapp.h
 *
 * Created on 26/8/2019
 */
#ifndef SERVERAPP_H
#define SERVERAPP_H

#define SERVER_NAME "Socket Chat Server"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sysexits.h>
#include <unistd.h>
#include <string>
#include <thread>
#include <vector>

#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/ServerApplication.h>
#include "messages/MessageClientReqRegister.h"
#include "roomchat.h"
#include "servercore.h"

using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::ServerApplication;
using std::thread;
using std::vector;
using RoomChatPtr = shared_ptr<RoomChat>;
class ServerApp : public ServerApplication {
private:
    inline static const int MAX_PENDING_CONNECTION{5};
    bool _isPrintHelp;
    int _sockDomain;
    int _inetPort;
    std::string _portOrUnixPath;

    std::unique_ptr<ServerCore> _serverHandlerPtr;
    RoomChatPtr _publicRoom;
    vector<RoomChatPtr> _privatesRoom;

public:
    ServerApp();
    // Necessary override methods
    virtual void initialize(Application &self) override;
    virtual void uninitialize() override;
    virtual void reinitialize(Application &selft) override;
    virtual void defineOptions(OptionSet &options) override;
    virtual void handleOption(const std::string &name, const std::string &value) override;
    // user defined
    void handlePrintHelp() const;
    // The server main function
    virtual int main(const std::vector<std::string> &args) override;
    virtual const char *name() const override;

    // temp handler
    void handleNewConnection(int clientSocket);
};

#endif	// SERVERAPP_H
