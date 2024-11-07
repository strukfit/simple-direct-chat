#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>
#include <memory>
#include <unordered_map>
#include <string>
#include <iostream>

using boost::asio::ip::tcp;


class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(tcp::socket socket, std::unordered_map<int, std::shared_ptr<Session>>& clients, int id);

	void start();
	void deliver(const std::string& msg);
	int get_id() const;

private:
	void init_command_handlers();
	void send_client_list();
	void handle_chat_command(const std::string& args);
	void handle_exit_command();
	void handle_default_message(const std::string& message);
	void do_read();

	std::unordered_map<std::string, std::function<void(const std::string&)>> command_handlers_;
	tcp::socket socket_;
	std::unordered_map<int, std::shared_ptr<Session>>& clients_;
	std::string data_;
	int client_id_;
	int target_id_;
};

#endif // SESSION_H