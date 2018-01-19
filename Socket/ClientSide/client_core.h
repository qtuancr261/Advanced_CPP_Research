#ifndef CLIENT_CORE_H
#define CLIENT_CORE_H
#include <sys/socket.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdio>
#include <fstream>
#include <thread>
#include <fstream>
#include <iostream>
using std::ifstream;
using std::ofstream;
using std::ios;
using std::cout;
using std::string;
class Client_Core
{
private:
    string fileName;
    string fileName_recv;
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
    void getBinaryDataFromFile();
    void writeBinaryDataFromFile();
    void createMessageForSendFile();
    bool DoesClientRequestSendFile();
    bool DoesClientRequestRecvFile();

    void exec();
};

#endif // CLIENT_CORE_H
