#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <string>

using boost::asio::ip::tcp;

void read_messages(tcp::socket& socket)
{
	boost::asio::streambuf buffer;
	while (true)
	{
		boost::system::error_code ec;
		size_t bytes_transferred = socket.read_some(buffer.prepare(1024), ec);

		if (ec)
		{
			if (ec == boost::asio::error::eof)
			{
				std::cout << "Connection closed by server." << std::endl;
				return;
			}
			else
			{
				throw boost::system::system_error(ec);
			}
		}

		buffer.commit(bytes_transferred);
		std::string message(buffers_begin(buffer.data()), buffers_end(buffer.data()));
		buffer.consume(buffer.size());
		std::cout << message;
	}
}

int main() 
{
	try 
	{
		boost::asio::io_context io_context;
		tcp::socket socket(io_context);
		socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));

		std::thread(read_messages, std::ref(socket)).detach();

		std::string input;
		std::cout << "Use '/list' to view clients, '/chat <ID>' to select a client, and '/exit' to leave chat.\n";

		while (true)
		{
			std::getline(std::cin, input);
			if (!input.empty()) {
				input += "\n";
				boost::asio::write(socket, boost::asio::buffer(input));
			}	
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
	return 0;
}