#include <QCoreApplication>
#include "client_core.h"
int main(int argc, char *argv[])
{
    Client_Core client;
    client.exec();
    std::thread myThreadS(&Client_Core::handleSendStream, &client);
    myThreadS.join();
    return 0;
}
