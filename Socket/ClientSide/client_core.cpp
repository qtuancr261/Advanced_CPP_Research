#include "client_core.h"

Client_Core::Client_Core()
    : fileName{nullptr}, binaryData{nullptr}, message{nullptr}, dataSize{0}, clientFD{-1}, MESSAGE_SIZE{200}

{
    clientFD = socket(AF_INET, SOCK_STREAM, 0);
    if (clientFD < 0)
    {
        printf("Couldn't create socket");
        exit(EXIT_FAILURE);
    }
}

bool Client_Core::connectToServer(int serverPort, const char *serverAddress) const
{
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(serverPort);
    server.sin_addr.s_addr = inet_addr(serverAddress);
    if (connect(clientFD, (sockaddr*)&server, sizeof(server)) < 0)
        return false;
    return true;
}

void Client_Core::handleSendStream()
{
    while (true)
    {
        message = new char[MESSAGE_SIZE];
        fgets(message, 200, stdin);
        int send_size{send(clientFD, message, MESSAGE_SIZE, 0)};
        delete[] message;
        if (send_size <= 0)
            break;
    }
}
void Client_Core::exec()
{
    if(connectToServer(2610, "127.0.0.1"))
        printf(" -> connection successfully\n");
    else
        printf(" -> connection failed\n");
    /*pthread_t clientHandleSendThread{};
    if (pthread_create(&clientHandleSendThread, nullptr, wrapper_handlerSendStream, this) != 0)
    {
        printf(" -> create thread failed");
        exit(1);
    }*/

    //threadS = std::thread(&Client_Core::handleSendStream, this);
}
