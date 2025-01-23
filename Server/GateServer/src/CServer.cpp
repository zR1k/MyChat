#include "CServer.h"
#include "HttpConnection.h"
#include "AsioIOServicePoll.h"


CServer::CServer(boost::asio::io_context& ioc, unsigned short& port) 
    : _acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _ioc(ioc) {
    
}

void CServer::Start()
{    
    auto self = shared_from_this();
    auto & io_context = AsioIOServicePoll::GetInstance()->GetIOService();
    std::shared_ptr<HttpConnection> connection = std::make_shared<HttpConnection>(io_context);
    _acceptor.async_accept(connection->GetSocket(), [self, connection](beast::error_code ec) {
        try {
            if (ec) {
                self->Start();
                return;
            }
            connection->Start();
            self->Start();
        }
        catch (std::exception& exp) {
            std::cout << "exception is " << exp.what() << std::endl;
            self->Start();
        }
    });
}