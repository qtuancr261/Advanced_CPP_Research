/*
 * Author: tuantq3
 * File: serverapp.h
 *
 * Created on 26/8/2019
 */
#ifndef SERVERAPP_H
#define SERVERAPP_H

#include "Poco/Util/Application.h"
#include "Poco/Util/OptionSet.h"

using Poco::Util::Application;
using Poco::Util::OptionSet;
class ServerApp : public Application {
private:
public:
    ServerApp();
    // Necessary override methods
    virtual void initialize(Application& self) override;
    virtual void uninitialize() override;
    virtual void reinitialize(Application& selft) override;
    virtual void defineOptions(OptionSet& options) override;
    virtual void handleOption(const std::string& name, const std::string& value) override;
    // The server main function
    virtual int main(const std::vector<std::string>& args) override;
};

#endif  // SERVERAPP_H
