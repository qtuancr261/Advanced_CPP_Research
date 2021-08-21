#include "serverapp.h"

ServerApp::ServerApp()
    : _isPrintHelp{false} {}

void ServerApp::initialize(Poco::Util::Application &self) {
    std::clog << " Initializing ...\n";
    addSubsystem(new ServerCore{"SocketServer", _sockDomain, SOCK_STREAM, _portOrUnixPath});
    ServerApplication::initialize(self);
}

void ServerApp::uninitialize() {
    std::clog << " Uninitializing ...\n";
    ServerApplication::uninitialize();
}

void ServerApp::reinitialize(Poco::Util::Application &selft) {}

void ServerApp::defineOptions(Poco::Util::OptionSet &options) {
    ServerApplication::defineOptions(options);
    options.addOption(Option("help", "h", "display help", false));
    options.addOption(Option("domain", "d", "set socket domain", true, "domain type", true));
    options.addOption(Option("port", "p", "set path for AF_UNIX or port for AF_INET/INET6", true, "port/path", true));
}

void ServerApp::handleOption(const std::string &name, const std::string &value) {
    if (name == "help") {
        std::cout << "Display help \n";
        _isPrintHelp = true;
        handlePrintHelp();
        stopOptionsProcessing();
        return;
    }
    if (name == "domain") {
        std::cout << "Domain type: " << value << std::endl;
        if (value == "AF_UNIX")
            _sockDomain = AF_UNIX;
        else if (value == "AF_INET")
            _sockDomain = AF_INET;
        else if (value == "AF_INET6")
            _sockDomain = AF_INET6;
        return;
    }
    if (name == "port") {
        std::cout << "Port/path: " << value << std::endl;
        _portOrUnixPath = value;
        return;
    }
}

void ServerApp::handlePrintHelp() const {
    auto itOptionBeg = options().begin();
    auto itOptionEnd = options().end();
    std::cout << "Usage\n";
    for (; itOptionBeg != itOptionEnd; ++itOptionBeg) {
        std::cout << " -" << itOptionBeg->shortName() << " --" << itOptionBeg->fullName() << " " << itOptionBeg->description() << "\n";
    }
}

int ServerApp::main(const std::vector<std::string> &args) {
    if (_isPrintHelp) {
        return EXIT_OK;
    }
    ServerApplication::instance().getSubsystem<ServerCore>().onRun();
    waitForTerminationRequest();
    ServerApplication::instance().getSubsystem<ServerCore>().onStop();
    return EX_OK;
}

const char *ServerApp::name() const { return SERVER_NAME; }

void ServerApp::handleNewConnection(int clientSocket) {
    /*
     * I/O on stream socket
     * ----------------     Kernel
     * ---------------- -> buffer -> ---------------
     * App A: sockfd -> [-----------] App B: sockfd
     * ---------------- <- buffer <- ---------------
     */
    string welcomeMsg{"Welcome to chat box ! Have a nive day"};
    // send(clientSocket, welcomeMsg.c_str(), welcomeMsg.size(), 0);
    MessageClientReqRegister req;
    shared_ptr<uint8_t[]> messageData{};
    size_t messageSize{};
    req.name = welcomeMsg;
    if (req.serialize(messageData, messageSize)) {
        cout << "Framsize " << req.frameSize << endl;
        send(clientSocket, messageData.get(), messageSize, 0);
    }

    close(clientSocket);
    std::cout << "Close connection ....... \n";
}
