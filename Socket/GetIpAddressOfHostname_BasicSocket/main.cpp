#include <cstdlib>
#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <netdb.h> // hostent
#include <arpa/inet.h>
// Get ip address of hostname tp connect to a remote host
using namespace std;
int main(int argc, char *argv[])
{
    char hostName[]{"localhost"};
    char ip[100]{};
    hostent* ptrHostent{gethostbyname(hostName)};
    in_addr** ptrAddress_List{};
    if (ptrHostent  == nullptr)
    {
        herror("gethostbyname");
        exit(1);
    }
    ptrAddress_List = (in_addr**)ptrHostent->h_addr_list;
    for (int i{}; ptrAddress_List[i] != nullptr; i++)
    {
        strcpy(ip, inet_ntoa(*ptrAddress_List[i]));
    }
    cout << hostName << " : " << ip << endl;
    return 0;
}
