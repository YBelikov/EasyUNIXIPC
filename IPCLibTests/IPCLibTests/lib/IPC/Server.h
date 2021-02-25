//
//  Server.h
//  ipc
//
//  Created by Yuriy Belikov on 29.12.2020.
//

#ifndef Server_h
#define Server_h

#include <memory>
#include <thread>
#include "Socket.h"

#pragma GCC visibility push(default)

class Server
{

public:
    int Start();
    int Send(const char* message, ssize_t messageLength);
    int Receive(char** message, ssize_t& messageLength);
    
private:
    int SetServerSocketFileDescriptor();
    int AcceptConnections();
    int Bind();
    void DoJob(int clientSocketFD);
    void InitializeServer();
    
private:
    Socket mServerSocket{};
    Socket mClientSocket{};
    std::thread mAcceptanceThread{};
};
  

#pragma GCC visibility pop

#endif /* Server_h */

