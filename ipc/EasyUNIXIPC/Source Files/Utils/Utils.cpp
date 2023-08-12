//
//  Utils.cpp
//  ipc
//
//  Created by Yuriy Belikov on 11.01.2021.
//

#include <unistd.h>
#include <errno.h>
#include "Utils.h"


int Utils::SendMessageLength(const Socket* socket, ssize_t messageLength)
{
    int bytesToWrite = sizeof(messageLength);
    char* data = reinterpret_cast<char*>(&messageLength);
    do
    {
        ssize_t bytesWritten = write(socket->GetFileDescriptor(), data, bytesToWrite);
        if (bytesWritten < 0)
        {
            return errno;
        }
        bytesToWrite -= bytesWritten;
        data += bytesWritten;
        
    }
    while (bytesToWrite > 0);
    return 0;
}

int Utils::ReceiveMessageLength(const Socket* socket, ssize_t& messageLength)
{
    messageLength = 0;
    int bytesToRead = sizeof(messageLength);
    char* data = reinterpret_cast<char*>(&messageLength);
    do
    {
        ssize_t bytesRead = read(socket->GetFileDescriptor(), data, bytesToRead);
        if (bytesRead < 0)
        {
            return errno;
        }
        bytesToRead -= bytesRead;
        data += bytesRead;
        
    }
    while (bytesToRead > 0);
    return 0;
}
