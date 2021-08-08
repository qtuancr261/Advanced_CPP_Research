#include "client_core.h"

Client_Core::Client_Core()
    : fileName{}
    , binaryData{nullptr}
    , send_message{nullptr}
    , dataSize{0}
    , _clientfd{-1}
    , MESSAGE_SIZE{200}
    , RECV_MESSAGE_SIZE{200000}

{
    _clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_clientfd < 0) {
        printf("Couldn't create socket");
        exit(EXIT_FAILURE);
    }
}

Client_Core::Client_Core(const std::string& sysName,
                         int sockDomain,
                         int sockType,
                         const std::string& host,
                         const std::string& portOrPath,
                         const std::string& clientName)
    : userName{clientName}
    , fileName{}
    , binaryData{nullptr}
    , send_message{nullptr}
    , dataSize{0}
    , _clientfd{-1}
    , MESSAGE_SIZE{200}
    , RECV_MESSAGE_SIZE{200000}
    , _sysName{sysName}
    , _sockDomain{sockDomain}
    , _sockType{sockType}
    , _host{host}
    , _inetPort{0}
    , _unixPath{"/tmp/afunix"} {
    switch (_sockDomain) {
        case AF_UNIX:
            _unixPath = portOrPath;
            break;
        case AF_INET:
        case AF_INET6:
            try {
                _inetPort = std::stoi(portOrPath);
            } catch (const std::exception& exception) {
                std::cerr << "ClientCore error: " << exception.what();
            }
            break;
    }
}

Client_Core::~Client_Core() {}

const char* Client_Core::name() const { return _sysName.c_str(); }

void Client_Core::initialize(Application& app) {
    if (initSocket() != 0) {
        _clientfd = -1;
    }
}

void Client_Core::uninitialize() {}

void Client_Core::onRun() {
    // connect to server
    connectToServer();
    // handle communication with server
    sendMessage();
    recvMessage();
}

void Client_Core::onStop() {}

int Client_Core::initSocket() {
    _clientfd = socket(_sockDomain, _sockType, 0);
    if (_clientfd < 0) {
        std::cerr << "Error when create socket";
        return EX_OSERR;
    }
    return 0;
}

bool Client_Core::connectToServer() const {
    switch (_sockDomain) {
        case AF_UNIX: {
            sockaddr_un serveraddr;
            memset(&serveraddr, 0, sizeof(sockaddr_un));
            serveraddr.sun_family = _sockDomain;
            if (_unixPath.size() > (sizeof(sockaddr_un::sun_path) - 1)) {
                std::cerr << "unix path size must be smaller than " << sizeof(sockaddr_un::sun_path);
                return EX_IOERR;
            }
            strncpy(serveraddr.sun_path, _unixPath.c_str(), _unixPath.size());
            /* System call: connect(sockfd, struct sockaddr*, socklent_t)
             * - connect the active socket referred to by the socketfd to the listening socket- specified by sockaddr* and socklen_t
             */
            if (connect(_clientfd, (sockaddr*)&serveraddr, sizeof(sockaddr_un)) < 0) return EX_TEMPFAIL;
            break;
        }

        case AF_INET:
            break;
        case AF_INET6:
            break;
    }
    //    sockaddr_in server;
    //    server.sin_family = AF_INET;
    //    server.sin_port = htons(serverPort);
    //    server.sin_addr.s_addr = inet_addr(serverAddress);

    //    if (connect(_clientfd, (sockaddr*)&server, sizeof(server)) < 0) return false;
    //    return true;
    std::clog << "Established connection ...\n";
    return true;
}

void Client_Core::sendMessage() {
    std::cout << "Name " << userName << std::endl;
    write(_clientfd, userName.data(), userName.size());
}

void Client_Core::recvMessage() {
    char tmpBuf[1000];
    while (true) {
        while (read(_clientfd, tmpBuf, 1000) > 0) {
            std::cout << "From server " << tmpBuf << std::endl;
        }
    }
}

void Client_Core::handleSendStream() {
    send(_clientfd, userName.data(), userName.size(), 0);
    while (true) {
        int send_size{};
        send_message = new char[MESSAGE_SIZE];
        fgets(send_message, MESSAGE_SIZE, stdin);
        if (DoesClientRequestSendFile()) {
            char* subString{strtok(send_message, " ")};
            subString = strtok(nullptr, " ");
            fileName = QString(subString);
            fileName.chop(1);
            send_size = 1;
            if (getBinaryDataFromFile()) {
                createMessageForSendFile();
                send_size = send(_clientfd, send_message_file.get(), strlen(send_message_file.get()), 0);
                fgets(subString, 100, stdin);
                send_size = send(_clientfd, binaryData, dataSize, 0);
            }
        } else
            send_size = send(_clientfd, send_message, strlen(send_message), 0);
        delete[] send_message;
        // delete[] binaryData;
        if (send_size <= 0) break;
    }
}

void Client_Core::handleReceiveStream() {
    //    while (true) {
    //        recv_message = new char[RECV_MESSAGE_SIZE];
    //        int recv_size{static_cast<int>(recv(clientFD, recv_message, RECV_MESSAGE_SIZE, 0))};
    //        printf("-> %s \n", recv_message);
    //        if (DoesClientRequestRecvFile()) {
    //            // char* subString{strtok(recv_message, " ")};
    //            QString message(recv_message);
    //            // subString = strtok(nullptr, " ");
    //            // fileName_recv = QString(subString);
    //            fileName_recv = message.section(" ", -2, -2);
    //            // fileName_recv.pop_back();
    //            // dataSize_recv = std::stoi(string(strtok(nullptr, " ")));
    //            dataSize_recv = message.section(" ", -1, -1).toInt();
    //            // cout << fileName_recv << " -> " << dataSize_recv;
    //            binaryData_recv = new char[dataSize_recv]{};
    //            recv(clientFD, recv_message, RECV_MESSAGE_SIZE, 0);
    //            recv_size = recv(clientFD, binaryData_recv, dataSize_recv, 0);
    //            writeBinaryDataFromFile();
    //        }
    //        delete[] recv_message;
    //        // delete[] binaryData_recv;
    //        if (recv_size == 0) break;
    //    }
    while (true) {
        uint8_t* data = new uint8_t[4];
        read(_clientfd, data, 4);
        size_t framSize = *(uint32_t*)data;
        std::cout << "Framsize " << framSize << std::endl;
        shared_ptr<uint8_t[]> messageData{new uint8_t[framSize]};
        BufferWrapper wrap(messageData.get(), framSize);
        wrap.writeInt(framSize);
        read(_clientfd, messageData.get() + 4, framSize);
        MessageClientReqRegister mess{};
        mess.deserialize(messageData, framSize);
        std::cout << "Name " << mess.name << std::endl;
        break;
    }
}

bool Client_Core::getBinaryDataFromFile() {
    ifstream file{fileName.toStdString(), ios::in | ios::ate | ios::binary};
    if (file.is_open()) {
        dataSize = static_cast<int>(file.tellg());
        binaryData = new char[dataSize]{};
        file.seekg(0, ios::beg);
        file.read(binaryData, dataSize);
        // cout << binaryDataFromFile << endl;
        file.close();
        return true;
    }
    printf("open file failed\n");
    return false;
}

void Client_Core::writeBinaryDataFromFile() {
    ofstream fileO{fileName_recv.toStdString(), ios::out | ios::ate};
    if (fileO.is_open()) {
        // cout << "Ok - O";
        fileO.seekp(0, ios::beg);
        fileO.write(binaryData_recv, dataSize_recv);
        fileO.close();
    } else
        cout << "error - O";
}

void Client_Core::createMessageForSendFile() {
    send_message_file.reset(new char[MESSAGE_SIZE]{});
    strcat(send_message_file.get(), "<FILE>");
    strcat(send_message_file.get(), " ");
    strcat(send_message_file.get(), fileName.toStdString().data());
    strcat(send_message_file.get(), " ");
    strcat(send_message_file.get(), std::to_string(dataSize).data());
    cout << send_message_file.get();
}

bool Client_Core::DoesClientRequestSendFile() {
    static const char SEND_FILE_HEADER[]{"<FILE>"};
    return (strstr(send_message, SEND_FILE_HEADER) != nullptr ? true : false);
}

bool Client_Core::DoesClientRequestRecvFile() {
    static const char SEND_FILE_HEADER[]{"<FILE>"};
    return (strstr(recv_message, SEND_FILE_HEADER) != nullptr ? true : false);
}
