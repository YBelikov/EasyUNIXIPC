#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <vector>
#include <iostream>
#include <functional>
#include "Server.h"


int Server::Start()
{
    mAcceptanceThread = std::thread(&Server::InitializeServer, this);
    return 0;
}

int Server::SetServerSocketFileDescriptor()
{
    int socketFD = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socketFD < 0)
    {
        return errno;
    }
    mServerSocket.SetFileDescriptor(socketFD);
    return 0;
}

int Server::Bind()
{
    sockaddr_un* address = mClientSocket.GetSocketAddressPtr();
    unlink(mServerSocket.GetSocketPath().c_str());
    int bindResult = bind(mServerSocket.GetFileDescriptor(), reinterpret_cast<sockaddr*>(address), mServerSocket.GetLength());
    return bindResult < 0 ? errno : 0; 
}


int Server::AcceptConnections()
{
    listen(mServerSocket.GetFileDescriptor(), 5);
    socklen_t clientLength = mClientSocket.GetLength();
    sockaddr_un* address = mClientSocket.GetSocketAddressPtr();
    int clientSocketFD = accept(mServerSocket.GetFileDescriptor(), reinterpret_cast<sockaddr*>(address), &clientLength);
    if (clientSocketFD < 0)
    {
        return errno;
    }
    mClientSocket.SetFileDescriptor(clientSocketFD);
    return 0;
}

int Server::Send(const char* message, ssize_t messageLength)
{
    if (message == nullptr)
    {
        return EFAULT;
    }
    ssize_t bytesWritten = write(mClientSocket.GetFileDescriptor(), &messageLength, sizeof(ssize_t));
    if (bytesWritten < 0)
    {
        return errno;
    }
    bytesWritten = write(mClientSocket.GetFileDescriptor(), message, messageLength);
    return bytesWritten > 0 ? 0 : errno;
}

int Server::Send(bool response)
{
    ssize_t bytesWritten = write(mClientSocket.GetFileDescriptor(), &response, sizeof(bool));
    return bytesWritten > 0 ? 0 : errno;
}

int Server::Receive(char** message, ssize_t& messageLength) 
{
    if (mAcceptanceThread.joinable())
    {
        mAcceptanceThread.join();
    }
    ssize_t bytesRead = read(mClientSocket.GetFileDescriptor(), &messageLength, sizeof(ssize_t));
    if (bytesRead <= 0)
    {
        return errno;
    }
    
    *message = new char[messageLength];
    bytesRead = read(mClientSocket.GetFileDescriptor(), *message, messageLength);
    if (bytesRead <= 0)
    {
        return errno;
    }
    return 0;
}

void Server::InitializeServer()
{
    SetServerSocketFileDescriptor();
    Bind();
    AcceptConnections();
}
