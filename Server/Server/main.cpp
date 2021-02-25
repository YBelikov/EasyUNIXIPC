#include <iostream>
#include <string>
#include "Server.h"

int main(int argc, const char * argv[])
{
    std::string response;
    Server server;
    server.Start();
    char* responseBuffer = nullptr;
    ssize_t responseLength = 0;
    int counter = 0;
    while (true)
    {
        if (server.Receive(&responseBuffer, responseLength) != 0)
        {
            std::cout << "Error on receive\n";
        }
        std::string message(responseBuffer, responseBuffer + responseLength);
        std::cout << message <<'\n';
        delete [] responseBuffer;
        std::cin >> response;
        if (response == "exit")
        {
            break;
        }
        if (server.Send(response.data(), response.size()) != 0)
        {
            std::cout << "Response sending error\n";
        }
        ++counter;
    }
    return 0;
}

