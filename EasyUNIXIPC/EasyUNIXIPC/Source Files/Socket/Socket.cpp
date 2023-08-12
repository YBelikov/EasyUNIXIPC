#include <stdio.h>
#include <unistd.h>
#include <string>
#include "Socket.h"

const std::string Socket::sPATH = "/tmp/socket";

Socket::Socket() : mSocketFileDescriptor(-1)
{
    mSockAddr.sun_family = AF_UNIX;
    strncpy(mSockAddr.sun_path, sPATH.data(), sPATH.size());
    mLength = sizeof(mSockAddr);
}

void Socket::SetFileDescriptor(int socketFD)
{
    mSocketFileDescriptor = socketFD;
}

int Socket::GetFileDescriptor() const
{
    return mSocketFileDescriptor;
}

socklen_t Socket::GetLength() const
{
    return mLength;
}

sockaddr_un* Socket::GetSocketAddressPtr()
{
    return &mSockAddr;
}

const std::string Socket::GetSocketPath() const
{
    return sPATH;
}

Socket::~Socket()
{
    close(mSocketFileDescriptor);
}

