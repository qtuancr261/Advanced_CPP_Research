#ifndef CLIENTAPP_H
#define CLIENTAPP_H

#include <Poco/Util/Application.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/ServerApplication.h>
#include <string>
#include <vector>
#include "client_core.h"

using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::ServerApplication;

class ClientApp : public ServerApplication {
private:
    bool _isPrintHelp;
    int _sockDomain;
    //    int _sockType;
    std::string _host;
    int _inetPort;
    std::string _portOrUnixPath;
    std::string _clientName;

public:
    ClientApp();
    ~ClientApp();
    // Necessary override methods
    virtual void initialize(Application& self) override;
    virtual void uninitialize() override;
    virtual void defineOptions(OptionSet& options) override;
    virtual void handleOption(const std::string& name, const std::string& value) override;

    // User defined methods

    void _handlePrintHelp();

    virtual int main(const std::vector<std::string>& args) override;

    // user methods
};

#endif	// CLIENTAPP_H
