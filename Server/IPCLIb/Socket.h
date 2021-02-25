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
    static const std::string sPATH_;
    int socketFileDescriptor_;
    sockaddr_un sockAddr_{};
    socklen_t length_;
};


#endif /* Socket_h */
