#ifndef Socket_h
#define Socket_h

#include <sys/un.h>
#include <sys/socket.h>
#include <string>

class Socket
{
public:
    Socket();
    ~Socket();
    void SetFileDescriptor(int socketFD);
    int GetFileDescriptor() const;
    sockaddr_un* GetSocketAddressPtr();
    socklen_t GetLength() const;
    const std::string GetSocketPath() const;
    
private:
    static const std::string sPATH;
    int mSocketFileDescriptor;
    sockaddr_un mSockAddr{};
    socklen_t mLength;
};

#endif /* Socket_h */
