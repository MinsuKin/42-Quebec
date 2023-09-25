#pragma once

#include "command.hpp"

namespace Command
{
	bool pass(const Command& command, Client* client);
	bool nick(const Command& command, Client* client);
	bool user(const Command& command, Client* client);
	bool privmsg(const Command& command, Client* client);
	bool quit(const Command& command, Client* client);
	bool ping(const Command& command, Client* client);
	bool pong(const Command& command, Client* client);
	bool cap(const Command& command, Client* client);
	bool oper(const Command& command, Client* client);
	bool mode(const Command& command, Client* client);
	bool join(const Command& command, Client* client);
	bool kick(const Command& command, Client* client);
	bool invite(const Command& command, Client* client);
	bool topic(const Command& command, Client* client);
	bool part(const Command& command, Client* client);
}
