#ifndef SERVERCORE_H
#define SERVERCORE_H

#include <Poco/Util/Subsystem.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sysexits.h>
#include <unistd.h>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using Poco::Util::Application;
using Poco::Util::Subsystem;

class ServerCore : public Subsystem {
private:
    std::string _sysName;
    int _sockfd;
    int _sockDomain;
    int _sockType;
    int _inetPort;			// for AF_INET|AF_INET6
    std::string _unixPath;	// for AF_UNIX
    const int _MAX_PENDING_CONNECTION;
    const int _MAX_CONNECTED_CONNECTION;
    std::unique_ptr<std::thread> _entryAcceptThread;
    std::vector<std::unique_ptr<std::thread>> _connectionsHandler;

public:
    // Subsytem functions
    ServerCore(const std::string& sysName, int sockDomain, int sockType, const std::string& portOrPath);
    virtual ~ServerCore();
    virtual const char* name() const override;
    virtual void initialize(Application& app) override;
    virtual void uninitialize() override;
    void onRun();
    void onStop();
    // Handler functions
    int initSocket();
    int acceptHandler();
    int connectionsHandle(int clientFd);
};

#endif	// SERVERCORE_H
