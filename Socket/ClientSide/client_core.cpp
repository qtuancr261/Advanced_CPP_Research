#include "client_core.h"

Client_Core::Client_Core()
    : fileName{}, binaryData{nullptr}, send_message{nullptr}, dataSize{0}, clientFD{-1}, MESSAGE_SIZE{200}, RECV_MESSAGE_SIZE{200000}

{
    clientFD = socket(AF_INET, SOCK_STREAM, 0);
    if (clientFD < 0)
    {
        printf("Couldn't create socket");
        exit(EXIT_FAILURE);
    }
}

bool Client_Core::connectToServer(int serverPort, const char *serverAddress) const
{
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(serverPort);
    server.sin_addr.s_addr = inet_addr(serverAddress);
    if (connect(clientFD, (sockaddr*)&server, sizeof(server)) < 0)
        return false;
    return true;
}

void Client_Core::handleSendStream()
{
    while (true)
    {
        int send_size{};
        send_message = new char[MESSAGE_SIZE];
        fgets(send_message, MESSAGE_SIZE, stdin);
        if (DoesClientRequestSendFile())
        {
            char* subString{strtok(send_message, " ")};
            subString = strtok(nullptr, " ");
            fileName = string(subString);
            fileName.pop_back();
            getBinaryDataFromFile();
            cout << fileName << " : " << dataSize;
            createMessageForSendFile();
            send_size = send(clientFD, send_message_file, strlen(send_message_file), 0);
            fgets(subString, 100, stdin);
            send_size = send(clientFD, binaryData, dataSize, 0);
            delete[] send_message_file;
        }
        else
            send_size = send(clientFD, send_message, strlen(send_message), 0);
        delete[] send_message;
        if (send_size <= 0)
            break;
    }
}

void Client_Core::handleReceiveStream()
{
    while (true)
    {
        recv_message = new char[RECV_MESSAGE_SIZE];
        int recv_size{recv(clientFD, recv_message, RECV_MESSAGE_SIZE, 0)};
        printf("-> %s \n", recv_message);
        delete[] recv_message;
        if (recv_size == 0)
            break;
    }
}

void Client_Core::getBinaryDataFromFile()
{
    ifstream file{fileName, ios::in | ios::ate | ios::binary};
    if (file.is_open())
    {
        dataSize = static_cast<int>(file.tellg());
        binaryData = new char[dataSize]{};
        file.seekg(0, ios::beg);
        file.read(binaryData, dataSize);
        //cout << binaryDataFromFile << endl;
        file.close();
    }
    else
        printf("open failed");
}

void Client_Core::createMessageForSendFile()
{
    send_message_file = new char[MESSAGE_SIZE]{};
    strcat(send_message_file, "<FILE>");
    strcat(send_message_file, " ");
    strcat(send_message_file, fileName.data());
    strcat(send_message_file, " ");
    strcat(send_message_file, std::to_string(dataSize).data());
    cout << send_message_file;
}

bool Client_Core::DoesClientRequestSendFile()
{
    static const char SEND_FILE_HEADER[]{"<FILE>"};
    return (strstr(send_message, SEND_FILE_HEADER) != nullptr ? true : false);
}
void Client_Core::exec()
{
    if(connectToServer(2610, "127.0.0.1"))
        printf(" -> connection successfully\n");
    else
        printf(" -> connection failed\n");
    /*pthread_t clientHandleSendThread{};
    if (pthread_create(&clientHandleSendThread, nullptr, wrapper_handlerSendStream, this) != 0)
    {
        printf(" -> create thread failed");
        exit(1);
    }*/

    //threadS = std::thread(&Client_Core::handleSendStream, this);
}
