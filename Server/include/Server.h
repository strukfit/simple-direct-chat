#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <unordered_map>
#include "Session.h"

using boost::asio::ip::tcp;


class Server
{
public:
	Server(boost::asio::io_context& io_context, short port);

private:
	void do_accept();

	tcp::acceptor acceptor_;
	std::unordered_map<int, std::shared_ptr<Session>> clients_;
	int next_client_id_;
};

#endif // SERVER_H