#include <boost/asio.hpp>
#include "../include/Server.h"

int main()
{
	try {
		boost::asio::io_context io_context;
		Server server(io_context, 1234);
		std::cout << "Server launched successfully.\n";
		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
	return 0;
}