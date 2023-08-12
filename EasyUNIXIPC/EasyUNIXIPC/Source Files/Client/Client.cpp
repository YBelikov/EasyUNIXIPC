#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <errno.h>
#include "Client.h"

int Client::Connect()
{
    if (SetSocketFileDescriptor() != 0)
    {
        return errno;
    }
    sockaddr_un* address = mClientSocket.GetSocketAddressPtr();
    int connectionResult = connect(mClientSocket.GetFileDescriptor(), reinterpret_cast<sockaddr*>(address), mClientSocket.GetLength());
    return connectionResult < 0 ? errno : 0;
}

int Client::SetSocketFileDescriptor()
{
    int socketFD = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socketFD < 0)
    {
        return errno;
    }
    mClientSocket.SetFileDescriptor(socketFD);
    return 0;
}

int Client::Send(const char* message, ssize_t messageLength)
{
    if (message == nullptr)
    {
        return EFAULT;
    }
    
    ssize_t bytesWritten = write(mClientSocket.GetFileDescriptor(), &messageLength, sizeof(messageLength));
    if (bytesWritten < 0)
    {
        return errno;
    }
    bytesWritten = write(mClientSocket.GetFileDescriptor(), message, messageLength);
    return bytesWritten > 0 ? 0 : errno;
}

bool Client::Receive()
{
    bool response = false;
    ssize_t bytesRead = read(mClientSocket.GetFileDescriptor(), &response, sizeof(bool));
    return response;
}

int Client::Receive(char** message, ssize_t& messageLength)
{
    ssize_t bytesRead = read(mClientSocket.GetFileDescriptor(), &messageLength, sizeof(ssize_t));
    if (bytesRead < 0)
    {
        return errno;
    }
    *message = new char[messageLength];
    bytesRead = read(mClientSocket.GetFileDescriptor(), *message, messageLength);
    return bytesRead < 0 ? errno : 0;
}
