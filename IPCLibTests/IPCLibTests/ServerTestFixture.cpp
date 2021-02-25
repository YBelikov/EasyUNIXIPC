#include <vector>
#include <string>
#include <random>
#include "catch_amalgamated.hpp"
#include "Server.h"
#include "Client.h"

class ServerTestFixture
{
public:
    ServerTestFixture();

protected:
    std::vector<std::string> mRandomMessages;
    Server mServer;
    Client mClient;
};

ServerTestFixture::ServerTestFixture()
{
    mServer.Start();
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100ms);
    mClient.Connect();
}

TEST_CASE_METHOD(ServerTestFixture, "Start the server", "[randomLong]")
{
    const int conversationSize = 100;
    const int messageLength = 2000;
    const int lowBoundary = 65;
    const int highBoundary = 97;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(lowBoundary, highBoundary);
    for(int i = 0; i < conversationSize; ++i)
    {
        std::string message;
        for (int j = 0; j < messageLength; ++j)
        {
            message.push_back(static_cast<char>(distrib(gen)));
        }
        mRandomMessages.push_back(message);
    }
    char* buffer = nullptr;
    ssize_t length = 0;
    for (int i = 0; i < mRandomMessages.size() - 1; ++i)
    {
        DYNAMIC_SECTION("Message exchange" << i)
        {
            REQUIRE(mClient.Send(mRandomMessages[i].data(), mRandomMessages[i].size()) == 0);
            REQUIRE(mServer.Receive(&buffer, length) == 0);
            REQUIRE(length == mRandomMessages[i].size());
            REQUIRE(strncmp(buffer, mRandomMessages[i].data(), length) == 0);
            delete[] buffer;
            REQUIRE(mServer.Send(mRandomMessages[i + 1].data(), mRandomMessages[i + 1].size()) == 0);
            REQUIRE(mClient.Receive(&buffer, length) == 0);
            REQUIRE(length == mRandomMessages[i + 1].size());
            REQUIRE(strncmp(buffer, mRandomMessages[i + 1].data(), length) == 0);
            delete[] buffer;
        }
    }
}
