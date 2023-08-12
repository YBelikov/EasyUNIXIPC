#ifndef Client_h
#define Client_h

#include <memory>
#include "Socket.h"

#pragma GCC visibility push(default)

class Client
{
    
public:
    int Send(const char* message, ssize_t messageLength);
    int Receive(char** message, ssize_t& messageLength);
    bool Receive();
    int Connect();
    
private:
    int SetSocketFileDescriptor();
    
private:
    Socket mClientSocket_{};
};

#pragma GCC visibility pop

#endif /* Client_h */
