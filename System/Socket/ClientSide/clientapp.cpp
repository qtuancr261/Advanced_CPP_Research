#include "clientapp.h"

ClientApp::ClientApp() {}

ClientApp::~ClientApp() {}

void ClientApp::initialize(Application &self) {
    // to-do
    std::clog << "Initializing ...\n";
    addSubsystem(new Client_Core{"SocketClient", _sockDomain, SOCK_STREAM, _host, _portOrUnixPath, _clientName});
    ServerApplication::initialize(self);
}

void ClientApp::uninitialize() {
    std::clog << "Uninitializing ...\n";
    ServerApplication::uninitialize();
}

void ClientApp::defineOptions(Poco::Util::OptionSet &options) {
    Application::defineOptions(options);
    options.addOption(Option("help", "h", "display help", false));
    options.addOption(Option("domain", "d", "set socket domain", true, "domain type", true));
    options.addOption(Option("host", "o", "set host ", true, "hostname", true));
    options.addOption(Option("port", "p", "set path for AF_UNIX or port for AF_INET/INET6", true, "port/path", true));
    options.addOption(Option("name", "n", "set client name", true, "client name", true));
}

void ClientApp::handleOption(const std::string &name, const std::string &value) {
    if (name == "help") {
        _isPrintHelp = true;
        _handlePrintHelp();
        stopOptionsProcessing();
        return;
    }
    if (name == "name") {
        _clientName = value;
    }
    if (name == "domain") {
        std::cout << "Domain type: " << value << "\n";
        if (value == "AF_UNIX")
            _sockDomain = AF_UNIX;
        else if (value == "AF_INET")
            _sockDomain = AF_INET;
        else if (value == "AF_INET6")
            _sockDomain = AF_INET6;
        return;
    }
    if (name == "host") {
        _host = value;
    }
    if (name == "port") {
        _portOrUnixPath = value;
        return;
    }
}

void ClientApp::_handlePrintHelp() {
    auto itOptionBeg = options().begin();
    auto itOptionEnd = options().end();
    std::cout << " Usage\n";
    for (; itOptionBeg != itOptionEnd; ++itOptionBeg) {
        std::cout << " -" << itOptionBeg->shortName() << " --" << itOptionBeg->fullName() << " " << itOptionBeg->description() << "\n";
    }
}

int ClientApp::main(const std::vector<std::string> &args) {
    if (_isPrintHelp) {
        return EXIT_OK;
    }
    Application::instance().getSubsystem<Client_Core>().onRun();
    waitForTerminationRequest();
    Application::instance().getSubsystem<Client_Core>().onStop();
    return EXIT_OK;
}
