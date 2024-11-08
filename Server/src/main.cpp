#include <boost/asio.hpp>
#include "../include/Server.h"

int main(int argc, char* argv[])
{
	try {
		if (argc != 2)
		{
			std::cerr << "Usage: serverapp <port>" << std::endl;
			return 1; 
		}

		boost::asio::io_context io_context;
		short port = std::atoi(argv[1]);

		Server server(io_context, port);
		std::cout << "Server launched successfully.\n";

		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
	return 0;
}