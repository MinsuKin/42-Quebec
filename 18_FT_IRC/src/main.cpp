#include <iostream>
#include <cstdlib>
#include <sstream>

#include <signal.h>

#include "server/server.hpp"

void signal_handler(int signum)
{
	Server::shutdown();
	exit(signum);
}

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return 1;
	}

	std::stringstream ss(argv[1]);
	unsigned short port;
	ss >> port;
	if(ss.fail() || !ss.eof())
	{
		std::cerr << "Invalid port" << std::endl;
		return 1;
	}

	Server server;

	struct sigaction sigact;
	sigact.sa_handler = signal_handler;
	sigaction(SIGINT, &sigact, NULL);

	if(!Server::init(port, argv[2]))
	{
		std::cerr << "Failed to initialize server" << std::endl;
		return 1;
	}
	Server::run();
	Server::shutdown();

	return 0;
}
