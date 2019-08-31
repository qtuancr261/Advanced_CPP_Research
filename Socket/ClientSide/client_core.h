#ifndef CLIENT_CORE_H
#define CLIENT_CORE_H
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>
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
using std::cout;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::shared_ptr;
using std::string;
class Client_Core {
private:
    QString userName;
    QString fileName;
    QString fileName_recv;
    char* binaryData;
    char* binaryData_recv;
    char* send_message;
    char* send_message_file;
    char* recv_message;
    int dataSize;
    int dataSize_recv;
    int clientFD;
    const int MESSAGE_SIZE;
    const int RECV_MESSAGE_SIZE;

public:
    Client_Core();
    bool connectToServer(int serverPort, const char* serverAddress) const;
    void handleSendStream();
    void handleReceiveStream();
    bool getBinaryDataFromFile();
    void writeBinaryDataFromFile();
    void createMessageForSendFile();
    bool DoesClientRequestSendFile();
    bool DoesClientRequestRecvFile();

    void setClientName(QString userName);
};

#endif  // CLIENT_CORE_H
