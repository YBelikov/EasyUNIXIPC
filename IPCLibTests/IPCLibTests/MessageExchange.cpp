#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "Server.h"
#include "Client.h"

TEST_CASE("Hello message")
{
    Server server;
    server.Start();
    Client client;
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100ms);
    REQUIRE(client.Connect() == 0);
    std::string message = "hello";
    char* buffer = nullptr;
    ssize_t length = 0;
    REQUIRE(client.Send(message.data(), message.size()) == 0);
    server.Receive(&buffer, length);
    REQUIRE(length == message.size());
    REQUIRE(buffer != nullptr);
    REQUIRE(strncmp(buffer, message.data(), message.size()) == 0);
    delete[] buffer;
    
    REQUIRE(server.Send(message.data(), message.size()) == 0);
    REQUIRE(client.Receive(&buffer, length) == 0);
    REQUIRE(length == message.size());
    REQUIRE(buffer != nullptr);
    REQUIRE(strncmp(message.data(), buffer, message.size()) == 0);
    delete[] buffer;
    
}


TEST_CASE("Several different messages exchange")
{
    Server server;
    server.Start();
    Client client;
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100ms);
    client.Connect();
    std::vector<std::string> messages = {"Hello", "Hello from Morpheus", "What do you want?", "Follow the white rabbit.", "Why?!", "Just do it"};
    char* buffer = nullptr;
    ssize_t length = 0;
    for (int i = 0; i < messages.size() - 1; ++i)
    {
        DYNAMIC_SECTION("Message exchange" << i)
        {
            REQUIRE(client.Send(messages[i].data(), messages[i].size()) == 0);
            REQUIRE(server.Receive(&buffer, length) == 0);
            REQUIRE(length == messages[i].size());
            REQUIRE(strncmp(buffer, messages[i].data(), length) == 0);
            delete[] buffer;
            REQUIRE(server.Send(messages[i + 1].data(), messages[i + 1].size()) == 0);
            REQUIRE(client.Receive(&buffer, length) == 0);
            REQUIRE(length == messages[i + 1].size());
            REQUIRE(strncmp(buffer, messages[i + 1].data(), length) == 0);
            delete[] buffer;
        }
    }
}

