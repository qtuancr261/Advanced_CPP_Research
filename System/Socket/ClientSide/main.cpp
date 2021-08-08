#include <QCoreApplication>
#include "client_core.h"
#include "clientapp.h"
using std::endl;
int main(int argc, char* argv[]) {
    //    Client_Core client;
    //    if (argc < 2) {
    //        cout << "You must provide a name to join our server" << endl;
    //        return 1;
    //    }
    //    std::thread clientSendThread(&Client_Core::handleSendStream, &client);
    //    std::thread clientReceiveThread(&Client_Core::handleReceiveStream, &client);
    //    clientReceiveThread.join();
    //    clientSendThread.join();
    try {
        ClientApp app;
        return app.run(argc, argv);
    } catch (std::exception& exception) {
        std::clog << "Exception when run app: " << exception.what() << "\n";
    }
    return 0;
}
