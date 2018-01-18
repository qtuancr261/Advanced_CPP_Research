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
    char* binaryData;
    char* send_message;
    char* send_message_file;
    char* recv_message;
    int dataSize;
    int clientFD;
    const int MESSAGE_SIZE;
    const int RECV_MESSAGE_SIZE;
public:
    Client_Core();
    bool connectToServer(int serverPort, const char* serverAddress) const;
    void handleSendStream();
    void handleReceiveStream();
    void getBinaryDataFromFile();
    void createMessageForSendFile();
    bool DoesClientRequestSendFile();

    void exec();
};

#endif // CLIENT_CORE_H
