#include <boost/asio.hpp>
#include "../include/Server.h"

int main(int argc, char* argv[])
{
	try {
		SetThreadUILanguage(
			MAKELCID(
				MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
				SORT_DEFAULT
			)
		);
		 
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
	catch (boost::system::system_error& e)
	{
		std::cerr << "Error: " << e.code().message() << "\n";
		return 1;
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
	return 0;
}