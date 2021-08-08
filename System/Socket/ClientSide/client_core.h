#ifndef CLIENT_CORE_H
#define CLIENT_CORE_H

#include <Poco/Util/Subsystem.h>

#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sysexits.h>
#include <unistd.h>
#include <QString>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "messages/MessageClientReqRegister.h"
using Poco::Util::Application;
using Poco::Util::Subsystem;
using std::cout;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::shared_ptr;
using std::string;
class Client_Core : public Subsystem {
private:
    std::string userName;
    QString fileName;
    QString fileName_recv;
    char* binaryData;
    char* binaryData_recv;
    char* send_message;
    // char* send_message_file;
    std::unique_ptr<char[]> send_message_file;
    char* recv_message;
    int dataSize;
    int dataSize_recv;
    int _clientfd;
    const int MESSAGE_SIZE;
    const int RECV_MESSAGE_SIZE;
    std::string _sysName;
    int _sockDomain;
    int _sockType;
    std::string _host;
    int _inetPort;
    std::string _unixPath;

public:
    Client_Core();
    Client_Core(const std::string& sysName,
                int sockDomain,
                int sockType,
                const std::string& host,
                const std::string& portOrPath,
                const std::string& clientName);
    ~Client_Core();
    // Subsystem functions
    virtual const char* name() const override;
    virtual void initialize(Application& app) override;
    virtual void uninitialize() override;
    void onRun();
    void onStop();
    // Handle functions
    int initSocket();
    bool connectToServer() const;
    void sendMessage();
    void recvMessage();

    // legacy
    void handleSendStream();
    void handleReceiveStream();
    bool getBinaryDataFromFile();
    void writeBinaryDataFromFile();
    void createMessageForSendFile();
    bool DoesClientRequestSendFile();
    bool DoesClientRequestRecvFile();
};

#endif	// CLIENT_CORE_H
