#include <QCoreApplication>
#include "client_core.h"
int main(int argc, char *argv[])
{
    Client_Core client;
    for (int i{}; i < argc; i++)
        std::printf(argv[i]);
    client.exec(QString(argv[1]));
    std::thread myThreadS(&Client_Core::handleSendStream, &client);
    std::thread myThreadR(&Client_Core::handleReceiveStream, &client);
    myThreadS.join();
    myThreadR.join();
    return 0;
}
