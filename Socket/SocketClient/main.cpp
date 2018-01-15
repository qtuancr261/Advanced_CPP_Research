#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/sendfile.h>
#include <pthread.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const char SEND_FILE_HEADER_MESSAGE[]{"<FILE>"};
string getFileNameFromMessage(char* message)
{
    char* subString{};
    //char* fileName{};
    subString = strtok(message, " ");
    /*while(subString != nullptr)
    {
        fileName = subString;
        subString = strtok(nullptr, " ");
        //printf("part: %s", subString);
    }*/
    subString = strtok(nullptr, " ");
    return string(subString);
}
string readBinaryDataFromFile(string fileName)
{
    ifstream file{fileName, ios::in | ios::ate | ios::binary};
    if (file.is_open())
    {
        int binaryDataSize{static_cast<int>(file.tellg())};
        char* binaryDataFromFile{new char[binaryDataSize]{}};
        file.seekg(0, ios::beg);
        file.read(binaryDataFromFile, binaryDataSize);
        file.close();
        return string(binaryDataFromFile);
    }
    else
        printf("open failed");
    return nullptr;
}
string readBinaryDataFromMessage(char* message)
{
    char* subString{};
    //char* fileName{};
    subString = strtok(message, " ");
    /*while(subString != nullptr)
    {
        fileName = subString;
        subString = strtok(nullptr, " ");
        //printf("part: %s", subString);
    }*/
    subString = strtok(nullptr, " ");
    subString = strtok(nullptr, " ");
    return string(subString);
}
void writeBinaryDataToFile(string fileName, string binaryData)
{
    ofstream fileO{fileName, ios::out | ios::ate};
    if (fileO.is_open())
    {
        cout << "Ok - O" << endl;
        fileO.seekp(0, ios::beg);
        fileO.write(binaryData.c_str(), binaryData.length());
        fileO.close();
    }
    else
        cout << "error - O" ;
}
string createMessageForSendFile(string fileName, string binaryDataFromFile)
{
    return string(SEND_FILE_HEADER_MESSAGE) + " " + fileName + " " + binaryDataFromFile;
}
void* handlerSendStream(void* client_socket)
{
    int client_socketFD{*(int*)client_socket};
    while(true)
    {
        char messageFromClient[200]{};
        int send_size{};
        fgets(messageFromClient, 200, stdin);
        if (strstr(messageFromClient, SEND_FILE_HEADER_MESSAGE) != nullptr)
        {
            string fileName{getFileNameFromMessage(messageFromClient)};
            fileName.pop_back();
            string binaryData{readBinaryDataFromFile(fileName)};
            cout << createMessageForSendFile(fileName, binaryData);
            string message{createMessageForSendFile(fileName, binaryData)};
            send_size = send(client_socketFD, message.c_str(), message.length(), 0);
        }
        else
            send_size = send(client_socketFD, messageFromClient, strlen(messageFromClient), 0);

        if (send_size <= 0)
        {
             printf("server has been terminated");
             pthread_exit(nullptr);
        }
    }
}
void* handlerReceiveStream(void *client_socket)
{
    int client_socketFD{*(int*)client_socket};
    while(true)
    {
        int recv_size{};
        char messageFromServer[200]{};
        recv_size = recv(client_socketFD, messageFromServer, 200, 0);
        if (recv_size > 0)
        {
            printf("\n-> %s", messageFromServer);
            if (strstr(messageFromServer, SEND_FILE_HEADER_MESSAGE) != nullptr)
            {
                string filename = getFileNameFromMessage(messageFromServer);
                string data = string(strtok(nullptr, " "));
               writeBinaryDataToFile(filename, data);
            }
        }

        else if (recv_size == 0)
        {
             printf("server dis from recv");
             pthread_exit(nullptr);
        }
    }
}
int main(int argc, char *argv[])
{
    int client_socket{socket(AF_INET, SOCK_STREAM, 0)};
    if (client_socket < 0)
    {
        cerr << "Couldn't create socket ";
        exit(EXIT_FAILURE);
    }
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(2610);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(client_socket, (sockaddr*)&server, sizeof(server)) < 0)
        cerr << "Connection Failed";
    else
        cout << "Connection Successfully " << endl;
    int* ptrClient_socket{new int{client_socket}};
    pthread_t clientReceiveThread{};
    if (pthread_create(&clientReceiveThread, nullptr, handlerReceiveStream, (void*)ptrClient_socket) != 0)
    {
        cerr << "Client Receive Thread couldn't be created";
    }
    pthread_t clientSendThread{};
    if (pthread_create(&clientSendThread, nullptr, handlerSendStream, (void*)ptrClient_socket) != 0)
    {
        cerr << "Client Send Thread couldn't be created";
    }
    pthread_join(clientSendThread, nullptr);
    pthread_join(clientReceiveThread, nullptr);


    /*char messageFromServer[2000]{};
    if (recv(client_socket, messageFromServer, 2000, 0) > 0)
        cout << "->" << messageFromServer;
    char messageFromClient[2000]{};
    cin.getline(messageFromClient, 2000);
    send(client_socket, messageFromClient, strlen(messageFromClient), 0);*/
    close(client_socket);
    delete ptrClient_socket;
    return 0;
}
