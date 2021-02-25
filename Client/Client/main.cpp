#include <iostream>
#include "Client.h"

int main(int argc, const char * argv[])
{
    const std::string exitString = "exit";
    Client client;
    if (client.Connect() != 0)
    {
        std::cout << "Error while connecting to server\n";
        return -1;
    }
    
    int counter = 0;
    std::string message;
    char* responseBuffer = nullptr;
    long responseLength = 0;
    while (counter < 5 && message != exitString)
    {
        std::getline(std::cin, message);
        
        if (client.Send(message.data(), message.size()) != 0)
        {
            std::cout << "Sending message error!\n";
            break;
        }
        
        if (client.Receive(&responseBuffer, responseLength) != 0)
        {
            std::cout << "Error on receive\n";
            break;
        }
        std::string response(responseBuffer, responseBuffer + responseLength);
        std::cout << response << '\n';
        delete[] responseBuffer;
        ++counter;
    }
    return 0;
}
