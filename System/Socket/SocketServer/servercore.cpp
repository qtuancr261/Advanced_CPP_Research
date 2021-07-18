#include "servercore.h"

ServerCore::ServerCore(const std::string &sysName, int sockDomain, int sockType, const std::string &portOrPath)
    : _sysName{sysName}
    , _sockfd{-1}
    , _sockDomain{sockDomain}
    , _sockType{sockType}
    , _inetPort{0}
    , _unixPath{"/tmp/afunix"}
    , _MAX_PENDING_CONNECTION{10}
    , _MAX_CONNECTED_CONNECTION{100} {
    switch (_sockDomain) {
        case AF_UNIX:
            _unixPath = portOrPath;
            break;
        case AF_INET:
        case AF_INET6:
            try {
                _inetPort = std::stoi(portOrPath);
            } catch (const std::exception &exception) {
                std::cerr << "ServerCore error: " << exception.what();
            }
            break;
    }
}

ServerCore::~ServerCore() {}

const char *ServerCore::name() const { return _sysName.c_str(); }

void ServerCore::initialize(Poco::Util::Application &app) {
    if (initSocket() != 0) {
        _sockfd = -1;
    } else {
        // main thread - accept new connections:

        // handle new connections threads
        // up to max n connected client
        _connectionsHandler.reserve(_MAX_CONNECTED_CONNECTION);
    }
}
void ServerCore::uninitialize() {}

void ServerCore::onRun() {
    std::clog << "ServerCore::onRun \n";
    // main thread - accept new connections:
    _entryAcceptThread = std::make_unique<std::thread>(&ServerCore::acceptHandler, this);
    // handle new connections threads
    // up to max n connected client
}

void ServerCore::onStop() {
    for (auto &threads : _connectionsHandler) {
        threads->join();
    }

    _entryAcceptThread->join();
}

int ServerCore::initSocket() {
    /* System call: fd = socket(domain, type, protocol)
     *
     * Socket domains:                                                       Address structure   Address format
     * - AF_UNIX:  same host:                                                sockaddr_un         pathname
     * - AF_INET:  hosts connected via an IPv4 network:                      sockaddr_in         32-bit ipv4 address + 16-bit port number
     * - AF_INET6: hosts connected via an IPv6 network:                      sockaddr_in6        128-bit ipv6 address + 16 bit port number
     * - ...
     * Socket types:
     * - SOCK_STREAM: reliable, bidirectional, byte-stream -> TCP
     * - SOCK_DGRAM: connectionless -> UDP
     * - ...
     * Socket protocol: specified as 0 (non-0 protocol value are used with some socket types)
     *
     *
     */
    _sockfd = socket(_sockDomain, _sockType, 0);
    if (_sockfd < 0) {
        std::cerr << "Error when create socket";
        return EX_OSERR;
    }
    /* System call: bind(sockfd, struct sockaddr*, socklen_t)
     * - sockaddr* : structure specifying the address to which this sockfd is to be bound
     * type of structure passed depends on the socket domain: AF_INET -> sockaddr_in
     * ** struct sockaddr: generic socket address structure
     * {
     *    sa_family_t sa_family;   address family
     *    char        sa_data[14]; Socket address
     * }
     * - socklen_t : the size ofthe address structure
     */

    /* System call: listen(sockfd, backlog)
     * passive socket
     * the socket is used to accept connections from other (active) socket
     *
     */
    switch (_sockDomain) {
        case AF_UNIX: {
            sockaddr_un sockaddr;
            memset(&sockaddr, 0, sizeof(sockaddr_un));
            sockaddr.sun_family = _sockDomain;
            if (_unixPath.size() > (sizeof(sockaddr_un::sun_path) - 1)) {
                std::cerr << "unix path size must be smaller than " << sizeof(sockaddr_un::sun_path);
                return EX_IOERR;
            }
            if (remove(_unixPath.c_str()) < 0 && errno != ENOENT) {
                std::cerr << "Couldn't reuse " << _unixPath.c_str();
                return EX_TEMPFAIL;
            }
            strncpy(sockaddr.sun_path, _unixPath.c_str(), _unixPath.size());

            if (bind(_sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr_un)) < 0) {
                std::cerr << "bind socket failed ";
                return EX_TEMPFAIL;
            }
            listen(_sockfd, _MAX_PENDING_CONNECTION);
            break;
        }
        case AF_INET:
            break;
        case AF_INET6:
            break;
    }
    return 0;
}

int ServerCore::acceptHandler() {
    std::clog << "Running acceptHandler ...\n";
    while (true) {
        /* System call: accept(sockfd, struct sockadd*, socklen_t*)
         * Return: new socket that is connected to the peer socket that call connect()
         * - socklen_t* : point to an int that must be initialized to the size of the buffer pointed by sockadd*
         * - sockadd* : point to address of the peer socket
         * => BOTH sockadd* and socklen_t* could be specified as NULL if you're not interested in the address of the peer socket
         * => of course we can revive this info later by using getpeername() system call
         */
        int clientFd = accept(_sockfd, nullptr, nullptr);
        if (clientFd < 0) {
            std::cerr << "Error when accept new connection ";
            return EX_TEMPFAIL;
        }
        _connectionsHandler.push_back(std::make_unique<std::thread>(&ServerCore::connectionsHandle, this, clientFd));
    }
    return 0;
}

int ServerCore::connectionsHandle(int clientFd) {
    /*
     * I/O on stream socket
     * ----------------     Kernel
     * ---------------- -> buffer -> ---------------
     * App A: sockfd -> [-----------] App B: sockfd
     * ---------------- <- buffer <- ---------------
     */
    struct sockaddr *clientAddr{NULL};
    socklen_t clientAddrLen{0};
    switch (_sockDomain) {
        case AF_UNIX:
            struct sockaddr_un unixClient;
            clientAddr = (struct sockaddr *)&unixClient;
            // clientAddrLen = sizeof(sockaddr_un);
            getpeername(clientFd, clientAddr, &clientAddrLen);
            std::cout << " Running connectionHandler for: Client info " << unixClient.sun_path << "\n";
            break;
        case AF_INET:
            struct sockaddr_in inetClient;
            clientAddr = (struct sockaddr *)&inetClient;
            // clientAddrLen = sizeof(sockaddr_un);
            getpeername(clientFd, clientAddr, &clientAddrLen);
            std::cout << " Running connectionHandler for: Client info " << inetClient.sin_port << "\n";
            break;
        case AF_INET6:
            break;
    }
    close(clientFd);
    // getpeername(clientFd, )
    return 0;
}
