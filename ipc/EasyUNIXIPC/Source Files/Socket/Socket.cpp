#include <stdio.h>
#include <unistd.h>
#include <string>
#include "Socket.h"

const std::string Socket::sPATH_ = "/tmp/socket";

Socket::Socket() : socketFileDescriptor_(-1)
{
    sockAddr_.sun_family = AF_UNIX;
    strncpy(sockAddr_.sun_path, sPATH_.data(), sPATH_.size());
    length_ = sizeof(sockAddr_);
}

void Socket::SetFileDescriptor(int socketFD)
{
    socketFileDescriptor_ = socketFD;
}

int Socket::GetFileDescriptor() const
{
    return socketFileDescriptor_;
}

socklen_t Socket::GetLength() const
{
    return length_;
}

sockaddr_un* Socket::GetSocketAddressPtr()
{
    return &sockAddr_;
}

const std::string Socket::GetSocketPath() const
{
    return sPATH_;
}

Socket::~Socket()
{
    close(socketFileDescriptor_);
}

