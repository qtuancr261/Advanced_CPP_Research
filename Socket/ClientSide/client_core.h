#ifndef CLIENT_CORE_H
#define CLIENT_CORE_H
#include <sys/socket.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <pthread.h>
#include <cstdio>
#include <fstream>
#include <thread>
class Client_Core
{
private:
    char* fileName;
    char* binaryData;
    char* message;
    char* recv_message;
    int dataSize;
    int clientFD;
    const int MESSAGE_SIZE;
    const int RECV_MESSAGE_SIZE;
    std::thread threadS;
public:
    Client_Core();
    bool connectToServer(int serverPort, const char* serverAddress) const;
    void handleSendStream();
    void handleReceiveStream();
    void exec();
};

#endif // CLIENT_CORE_H
