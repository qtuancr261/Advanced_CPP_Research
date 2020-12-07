#include <QCoreApplication>
#include "client_core.h"
using std::endl;
int main(int argc, char *argv[])
{
    Client_Core client;
    if (argc < 2)
    {
        cout << "You must provide a name to join our server" << endl;
        return 1;
    }
    client.setClientName(QString(argv[1]));
    std::thread clientSendThread(&Client_Core::handleSendStream, &client);
    std::thread clientReceiveThread(&Client_Core::handleReceiveStream, &client);
    clientReceiveThread.join();
    clientSendThread.join();
    return 0;
}
