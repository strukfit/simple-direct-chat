#include "../include/Server.h"

Server::Server(boost::asio::io_context& io_context, short port):
	acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
	next_client_id_(1)
{
	do_accept();
}

void Server::do_accept()
{
	acceptor_.async_accept(
		[this](boost::system::error_code ec, tcp::socket socket)
		{
			if (!ec)
			{
				std::make_shared<Session>(std::move(socket), clients_, next_client_id_++)->start();
			}
			do_accept();
		}
	);
}
