#include "../include/Session.h"

Session::Session(tcp::socket socket, std::unordered_map<int, std::shared_ptr<Session>>& clients, int id):
	socket_(std::move(socket)),
	clients_(clients),
	client_id_(id),
	target_id_(-1)
{
	init_command_handlers();
}

void Session::start()
{
	send_client_list();
	do_read();
}

void Session::deliver(std::string& msg)
{
	write_data_ = std::move(msg);

	auto self(shared_from_this());
	boost::asio::async_write(socket_, boost::asio::buffer(write_data_),
		[this, self](boost::system::error_code ec, std::size_t)
		{
			if (ec)
			{
				std::cerr << "Error sending message: " << ec.message() << std::endl;
				clients_.erase(client_id_);
			}
		}
	);
}

int Session::get_id() const
{
	return client_id_;
}

void Session::init_command_handlers()
{
	command_handlers_["/list"] = [this](const std::string&) { send_client_list(); };
	command_handlers_["/chat"] = [this](const std::string& args) { handle_chat_command(args); };
	command_handlers_["/exit"] = [this](const std::string&) { handle_exit_command(); };
}

void Session::send_client_list()
{
	std::string client_list = "Clients online:\n";
	for (const auto& [id, _] : clients_)
	{
		if (id != client_id_)
		{
			client_list += "Client " + std::to_string(id) + "\n";
		}
	}
	deliver(client_list + "\n");
}

void Session::handle_chat_command(const std::string& args)
{
	try 
	{
		int target_id = std::stoi(args);
		if (!clients_.count(target_id) || target_id == client_id_)
		{
			deliver("Client " + std::to_string(target_id) + " not found or invalid.\n");
			return;
		}

		deliver("Now chatting with Client " + std::to_string(target_id) + ".\n");
	}
	catch (...)
	{
		deliver(std::string("Invalid client ID.\n"));
	}
}

void Session::handle_exit_command()
{
	target_id_ = -1;
	deliver(std::string("Exited chat. Choose another client.\n"));
}

void Session::handle_default_message(const std::string& message)
{
	if (target_id_ == -1)
	{
		deliver(std::string("No client selected. Use '/chat <ID>' to select a client.\n"));
		return;
	}

	std::string msg = "Client " + std::to_string(client_id_) + ": " + message;
	clients_[target_id_]->deliver(msg);
}

void Session::do_read()
{
	auto self(shared_from_this());
	boost::asio::async_read_until(socket_, boost::asio::dynamic_buffer(read_data_), "\n",
		[this, self](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				std::string message = read_data_.substr(0, length);
				read_data_.erase(0, length);

				message = message.substr(0, message.find_last_not_of("\n") + 1);

				auto space_pos = message.find(' ');
				std::string command = message.substr(0, space_pos);
				std::string args = space_pos == std::string::npos ? "" : message.substr(space_pos + 1);

				auto it = command_handlers_.find(command);
				if (it != command_handlers_.end())
				{
					it->second(args);
				}
				else
				{
					handle_default_message(message);
				}
			}
			else 
			{
				clients_.erase(client_id_);
			}

			do_read();
		}
	);
}
