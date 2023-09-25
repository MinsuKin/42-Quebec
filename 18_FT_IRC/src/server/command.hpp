#pragma once

#include <iostream>
#include <vector>

class Client;

namespace Command {
	enum Type {
		UNKNOWN = 0,
		PASS,
		NICK,
		USER,
		PRIVMSG,
		QUIT,
		PING,
		PONG,
		CAP,
		OPER,
		MODE,
		JOIN,
		KICK,
		INVITE,
		TOPIC,
		PART
	};
	// struct Prefix
	// {
	// 	std::string nick;
	// 	std::string user;
	// 	std::string host;
	// };
	struct Command {
		Type type;
		// Prefix prefix;
		std::vector<std::string> params;
	};

	bool parse(std::string command, Client* client);
	bool execute(const Command& command, Client* client);
}
