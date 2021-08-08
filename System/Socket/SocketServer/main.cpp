#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <thread>
#include "bufferwrapper.h"
#include "messages/MessageClientReqRegister.h"
#include "serverapp.h"

int main(int argc, char* argv[]) {
    //    BufferWrapper::serializeDeserializeNumber();
    //    BufferWrapper::serializeDeserializeString();
    //    MessageClientReqRegister::testSerializeDeserialize();
    try {
        ServerApp app;
        return app.run(argc, argv);
    } catch (Poco::Exception& exc) {
        std::cerr << exc.what();
    }
}
