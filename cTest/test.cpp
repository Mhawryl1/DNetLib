#include "Net.h"
#include "Socket.h"
#include <gtest/gtest.h>
#include <thread>

using namespace DNet;

class Server : public ::testing::Test
{
  protected:
    void SetUp() override
    {
    }
    void TearDown() override
    {
    }
    static DSocket socket;
    static EndPoint ep;
};

EndPoint Server::ep;
DSocket Server::socket;

class Client : public ::testing::Test
{
  protected:
    void SetUp() override
    {
    }
    void TearDown() override
    {
    }

  public:
    static DSocket socket;
    static EndPoint ep;
};

DSocket Client::socket;
EndPoint Client::ep;

TEST_F(Server, InitializeServerNetwork)
{
    EXPECT_EQ(Network::Initialize(), DNetResult::DNetSuccess);
}

TEST_F(Server, SetHostNameAndPortResolveHostIfReq)
{
    ep.SetHostNameAndPort("127.0.0.1", 8000);
    EXPECT_NE(ep.GetIPVersion(), IPVer::IPNOTVALID);
}
TEST_F(Server, CreateServerSocket)
{
    EXPECT_EQ(socket.Create(IPVer::IPV4), DNetResult::DNetSuccess);
}

TEST_F(Server, BindSocket)
{
    EXPECT_EQ(socket.Bind(ep), DNetResult::DNetSuccess);
}

TEST_F(Server, ListenSocket)
{
    EXPECT_EQ(socket.Listen(), DNetResult::DNetSuccess);
}

TEST_F(Server, AcceptConnection)
{
    // When
    std::thread([&]() {
        DNet::DSocket newSocket = socket.Accept();

        EXPECT_EQ(newSocket.SendHello(), DNet::DNetResult::DNetSuccess);
    }).detach();
}

//**Client**//
TEST_F(Client, InitializeClinetNetwork)
{
    EXPECT_EQ(Network::Initialize(), DNetResult::DNetSuccess);
}

TEST_F(Client, SetHostNameAndPortResolveHostIfReq)
{
    ep.SetHostNameAndPort("127.0.0.1", 8000);
}

TEST_F(Client, CreateClinetSocket)
{
    EXPECT_EQ(socket.Create(IPVer::IPV4), DNetResult::DNetSuccess);
}

TEST_F(Client, ConnectClientSocket)
{
    EXPECT_EQ(socket.Connect(ep), DNetResult::DNetSuccess);
}

TEST_F(Client, ClientReciveHelloMsg)
{
    std::string msg;

    if (socket.Recv() != SOCKET_ERROR)
    {
        for (size_t i = 0; i < socket.GetBuffer().size(); i++)
        {
            msg += socket.GetBuffer()[i];
        }
    }

    EXPECT_EQ(msg, "[ok signal] Hallo from server.");
}

//*Both*//
