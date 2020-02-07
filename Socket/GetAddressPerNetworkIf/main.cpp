#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <cstring>
using namespace std;
void showIPPerNetworkIf() {
    ifaddrs* ifaddr{nullptr};
    ifaddrs* ifa{nullptr};
    int family{}, s{};
    char host[NI_MAXHOST] {};

    if (getifaddrs(&ifaddr) == -1) {
        std::cerr << "get network interface failed ";
        return;
    }

    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == nullptr)
            continue;
        s = getnameinfo(ifa->ifa_addr, sizeof(sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
        if( /*(strcmp(ifa->ifa_name,"wlan0")==0)&&( */ ifa->ifa_addr->sa_family==AF_INET) // )
                {
                    if (s != 0)
                    {
                        printf("getnameinfo() failed: %s\n", gai_strerror(s));
                        exit(EXIT_FAILURE);
                    }
                    printf("\tInterface : <%s>\n",ifa->ifa_name );
                    printf("\t  Address : <%s>\n", host);
                }
            }

            freeifaddrs(ifaddr);
    }
int main() {
    showIPPerNetworkIf();
    return 0;
}
