#include "client_core.h"

Client_Core::Client_Core()
    : fileName{}
    , binaryData{nullptr}
    , send_message{nullptr}
    , dataSize{0}
    , clientFD{-1}
    , MESSAGE_SIZE{200}
    , RECV_MESSAGE_SIZE{200000}

{
    clientFD = socket(AF_INET, SOCK_STREAM, 0);
    if (clientFD < 0) {
        printf("Couldn't create socket");
        exit(EXIT_FAILURE);
    }
}

bool Client_Core::connectToServer(int serverPort, const char* serverAddress) const {
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(serverPort);
    server.sin_addr.s_addr = inet_addr(serverAddress);
    /* System call: connect(sockfd, struct sockaddr*, socklent_t)
     * - connect the active socket referred to by the socketfd to the listening socket- specified by sockaddr* and socklen_t
     */
    if (connect(clientFD, (sockaddr*)&server, sizeof(server)) < 0) return false;
    return true;
}

void Client_Core::handleSendStream() {
    send(clientFD, userName.toStdString().data(), strlen(userName.toStdString().data()), 0);
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
                send_size = send(clientFD, send_message_file, strlen(send_message_file), 0);
                fgets(subString, 100, stdin);
                send_size = send(clientFD, binaryData, dataSize, 0);
                delete[] send_message_file;
            }
        } else
            send_size = send(clientFD, send_message, strlen(send_message), 0);
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
        read(clientFD, data, 4);
        size_t framSize = *(uint32_t*)data;
        std::cout << "Framsize " << framSize << std::endl;
        shared_ptr<uint8_t[]> messageData{new uint8_t[framSize]};
        BufferWrapper wrap(messageData.get(), framSize);
        wrap.writeInt(framSize);
        read(clientFD, messageData.get() + 4, framSize);
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
    send_message_file = new char[MESSAGE_SIZE]{};
    strcat(send_message_file, "<FILE>");
    strcat(send_message_file, " ");
    strcat(send_message_file, fileName.toStdString().data());
    strcat(send_message_file, " ");
    strcat(send_message_file, std::to_string(dataSize).data());
    cout << send_message_file;
}

bool Client_Core::DoesClientRequestSendFile() {
    static const char SEND_FILE_HEADER[]{"<FILE>"};
    return (strstr(send_message, SEND_FILE_HEADER) != nullptr ? true : false);
}

bool Client_Core::DoesClientRequestRecvFile() {
    static const char SEND_FILE_HEADER[]{"<FILE>"};
    return (strstr(recv_message, SEND_FILE_HEADER) != nullptr ? true : false);
}
void Client_Core::setClientName(QString userName) {
    if (connectToServer(2610, "127.0.0.1"))
        printf(" -> connection successfully\n");
    else
        printf(" -> connection failed\n");
    this->userName = userName;
    /*pthread_t clientHandleSendThread{};
    if (pthread_create(&clientHandleSendThread, nullptr, wrapper_handlerSendStream, this) != 0)
    {
        printf(" -> create thread failed");
        exit(1);
    }*/

    // threadS = std::thread(&Client_Core::handleSendStream, this);
}
