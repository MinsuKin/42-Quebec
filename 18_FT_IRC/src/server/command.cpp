#include "command.hpp"

#include "irccommands.hpp"
#include "client.hpp"

namespace Command
{
	bool parse(std::string command, Client* client)
	{
		Command cmd;
		cmd.type = UNKNOWN;
		const char* const cmdList[] = \
			{"PASS", "NICK", "USER", "PRIVMSG",
			"QUIT", "PING", "PONG", "CAP", "OPER",
			"MODE", "JOIN", "KICK", "INVITE", "TOPIC",
			"PART"};

		if(command.empty())
			return false;

		size_t i = 0;
		if(command[0] == ':')
		{
			size_t pos = command.find(" ", 0);
			if(pos == std::string::npos)
				return false;
			i = pos + 1;
		}

		size_t y = 0;
		for(; y < sizeof(cmdList)/sizeof(char*); ++y)
			if(command.compare(i, command.find_first_of(" \r\n", i) - i, cmdList[y]) == 0)
			{
				cmd.type = (Type)(y + 1);
				break;
			}
		if(cmd.type == UNKNOWN)
			return false; // TODO: send error message or more
		i = command.find(' ', i + std::char_traits<char>::length(cmdList[y])) + 1;
		while(i < command.size())
		{
			if(command[i] == ':')
			{ // the rest is trailing
				cmd.params.push_back(command.substr(i + 1));
				break;
			}
			size_t pos = command.find(' ', i);
			cmd.params.push_back(command.substr(i, pos - i));
			i = command.find_first_not_of(' ', pos);
		}
		return execute(cmd, client);
	}

	bool execute(const Command& command, Client* client)
	{
		bool (* const cmdList[])(const Command&, Client*) = \
			{0, pass, nick, user, privmsg,
			quit, ping, pong, cap, oper, mode,
			join, kick, invite, topic, part};

		if(!client->registered() && command.type != CAP)
		{
			if(client->passworded())
			{
				if(command.type != NICK && command.type != USER)
					return false;
			}
			else
				if(command.type != PASS)
					return false;
		}

		return cmdList[command.type](command, client);
	}
}

