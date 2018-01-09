#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
using namespace std;
// Create a socket server
int main(int argc, char *argv[])
{
    int socket_desciptor{socket(AF_INET, SOCK_STREAM, 0)};
    if (socket_desciptor == -1)
        cerr << "Couldn't create socket" << endl;
    sockaddr_in server{};
    server.sin_port = htons(2610);
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    if (bind(socket_desciptor, (sockaddr*)(&server), sizeof(server)) < 0)
    {
        cerr << "bind failed";
        exit(1);
    }
    // listen
    listen(socket_desciptor, 3);
    cout << "Waiting for incoming connection " << endl;
    sockaddr_in client{};
    int client_size{};
    int new_socket{accept(socket_desciptor, (sockaddr*)&client, (socklen_t*)&client_size)};
    if (new_socket < 0)
    {
        cerr << "connection failed";
        exit(1);
    }
    cout << "connection accepted " << endl;
    char message[]{"Hello client"};
    //cout << strlen(message) << endl;
    write(new_socket, message, strlen(message));
    close(socket_desciptor);
    return 0;
}
