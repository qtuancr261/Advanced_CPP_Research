#include <QCoreApplication>
#include "client_core.h"
int main(int argc, char *argv[])
{
    Client_Core client;
    client.exec();
    std::thread myThreadS(&Client_Core::handleSendStream, &client);
    std::thread myThreadR(&Client_Core::handleReceiveStream, &client);
    myThreadS.join();
    myThreadR.join();
    return 0;
}
