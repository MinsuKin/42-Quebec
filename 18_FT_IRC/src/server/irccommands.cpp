#include "irccommands.hpp"
#include "client.hpp"
#include "channel.hpp"
#include "server.hpp"

#include <sstream>

namespace Command
{
	bool pass(const Command &command, Client *client)
	{
		if(!client->password(command.params[0]))
		{
			client->send("ERROR :Password incorrect\r\n");
			return false;
		}
		return true;
	}

	bool nick(const Command &command, Client *client)
	{
		if(Server::client(command.params[0]))
		{
			client->send("ERROR :Nickname already in use\r\n");
			return false;
		}
		if(!client->setnick(command.params[0]))
		{
			client->send("ERROR :Invalid nickname\r\n");
			return false;
		}
		return true;
	}

	bool user(const Command& command, Client* client)
	{
		// check if already registered
		if(client->registered())
		{
			client->send("You are already registered\r\n");
			return false;
		}
		// check parameters numbers
		if(command.params.size() < 4)
		{
			client->send("ERROR :Not enough parameters\r\n");
			return false;
		}
		else if(command.params.size() > 4)
		{
			client->send("ERROR :Too many parameters\r\n");
			return false;
		}
		// check nick is set
		if(client->nick().empty())
		{
			client->send("ERROR :No nickname given\r\n");
			return false;
		}
		// set user
		if(!client->setuser(command.params[0], command.params[3]))
		{
			client->send("ERROR :Invalid username\r\n");
			return false;
		}
		std::stringstream ss;
		ss << Server::clientCount();
		std::string clientCount = ss.str();

		client->send("001 " + client->nick() + " :Welcome to the Internet Relay Chat\r\n");
		client->send("002 " + client->nick() + " :Your host is " + Server::NAME + ", running version " + Server::VERSION + "\r\n");
		client->send("003 " + client->nick() + " :This server was created sometime ago" + "\r\n");
		client->send("004 " + client->nick() + " " + Server::NAME + "-" + Server::VERSION + " " + "o o" + "\r\n");
		client->send("005 " + client->nick() + " PREFIX=(o)@ CHANTYPES=# CHANMODES=,k,l,it :are supported by this server\r\n");

		client->send("251 " + client->nick() + " :There are " + clientCount + " users and 0 services on 1 server\r\n");

		return true;
	}

	bool privmsgToChannel(const Command& command, Client* client)
	{
		// check if channel exists
		Channel* msgTarget = Server::channel(command.params[0]);
		if(!msgTarget)
		{
			client->send("ERROR :No such channel\r\n");
			return false;
		}
		// check if client is in channel
		if(!msgTarget->isUserInChannel(client))
		{
			client->send("ERROR :You're not in that channel\r\n");
			return false;
		}
		// send message
		msgTarget->sendChannelMessage(client, command.params[1]);
		return true;
	}

	bool privmsgToUser(const Command& command, Client* client)
	{
		// check msgReceiver
		Client* msgTarget = Server::client(command.params[0]);
		if(!msgTarget)
		{
			client->send("ERROR :No such nick\r\n");
			return false;
		}
		if(!msgTarget->registered())
		{
			client->send("ERROR :msgTarget is not registered\r\n");
			return false;
		}
		// send message
		std::string msg = client->prefix() + " PRIVMSG " + msgTarget->nick() + ((command.params[1][0] == ':') ? " " : " :") + command.params[1] + "\r\n";

		msgTarget->send(msg.c_str());
		return true;
	}

	bool privmsg(const Command& command, Client* client)
	{
		// check parameters numbers
		if(command.params.size() < 2)
		{
			client->send("ERROR :Not enough parameters\r\n");
			return false;
		}
		// check msgTarget is channel or user
		std::string channelPrefixes = "#&+!";
		if(channelPrefixes.find(command.params[0][0]) == std::string::npos)
			return privmsgToUser(command, client);
		else
			return privmsgToChannel(command, client);
	}

	bool quit(const Command& command, Client* client)
	{
		if(command.params.size() < 1)
			return false;
		client->send("ERROR :Quit: " + command.params[0] + "\r\n");
		client->flagDisconnect = true;
		return true;
	}

	bool ping(const Command& command, Client* client)
	{
		if(command.params.size() < 1)
			return false;
		return Server::send("PONG " + command.params[0] + "\r\n", client);
	}

	bool pong(const Command& command, Client* client)
	{
		(void)client;
		if(command.params.size() < 1)
			return false;
		return true;
	}

	bool cap(const Command& command, Client* client)
	{
		if(command.params.size() < 1)
			return false;
		if(command.params[0] == "LS")
			client->send("CAP * LS\r\n");
		return true;
	}

	bool oper(const Command& command, Client* client)
	{
		if(command.params.size() < 2)
		{
			client->send(":" + Server::host() + " 461 " + client->nick() + " OPER :Not enough parameters.\r\n");
			return false;
		}

		if(!client->oper(command.params[0], command.params[1]))
		{
			client->send(":" + Server::host() + " 491 " + client->nick() + " :Invalid oper credentials\r\n");
			return false;
		}

		client->send(client->prefix() + " MODE " + client->nick() + " :+o\r\n");
		client->send(":" + Server::host() + " 381 " + client->nick() + " :You are now an IRC operator\r\n");

		return true;
	}

	static int parseMode(char mode)
	{
		for(size_t i = 0; i < std::char_traits<char>::length(Client::USERMODES); ++i)
			if(mode == Client::USERMODES[i])
				return 1 << i;
		return Client::MODE_UNKNOWN;
	}

	static int parseChanMode(char mode)
	{
		for(size_t i = 0; i < std::char_traits<char>::length(Channel::CHANMODES); ++i)
			if(mode == Channel::CHANMODES[i])
				return 1 << i;
		return Channel::MODE_UNKNOWN;
	}

	bool chanMode(const Command& command, Client* client)
	{
		if(command.params.size() < 2)
			return false;
		// check if the channel exists
		Channel* channel = Server::channel(command.params[0]);
		if(!channel)
		{
			client->send("ERROR :No such channel\r\n");
			return false;
		}
		if(!client->isoper() && !channel->isUserChannelOperator(client))
		{
			client->send("ERROR :You're not a channel operator\r\n");
			return false;
		}
		// parse the modes
		size_t i = 0;
		size_t argi = 2;
		if(command.params[1][0] != '+' && command.params[1][0] != '-')
			return false;
		std::string modestr;
		std::string argstr;
		bool unknown = false;
		while(i < command.params[1].size())
		{
			size_t j;
			modestr += command.params[1][i];
			for(j = i + 1; command.params[1][j] && command.params[1][j] != '+' && command.params[1][j] != '-'; ++j)
			{
				int r = parseChanMode(command.params[1][j]);
				if(r == Channel::MODE_UNKNOWN)
					unknown = true;
				else if(command.params[1][i] == '+')
				{
					switch(r)
					{
					case Channel::MODE_OP:
						if(command.params.size() <= argi)
							break;
						if(!channel->addChannelOperator(client, Server::client(command.params[argi++])))
							break;
						modestr += command.params[1][j];
						argstr += command.params[argi - 1] + " ";
						break;
					case Channel::MODE_INVITE_ONLY:
					case Channel::MODE_TOPIC_PROTECTED:
						if(channel->setMode(r))
							modestr += command.params[1][j];
						break;
					case Channel::MODE_LIMIT_USERS:
						if(!channel->setUserLimit(command.params[argi++]))
							break;
						modestr += command.params[1][j];
						argstr += command.params[argi - 1] + " ";
						break;
					case Channel::MODE_KEY_REQUIRED:
						if(!channel->setKey(command.params[argi++]))
							break;
						modestr += command.params[1][j];
						argstr += command.params[argi - 1] + " ";
						break;
					}
				}
				else if(command.params[1][i] == '-')
				{
					switch(r)
					{
					case Channel::MODE_OP:
						if(command.params.size() <= argi)
							break;
						if(!channel->removeChannelOperator(Server::client(command.params[argi++])))
						{
							client->send("ERROR: No such channel operator\r\n");
							break;
						}
						modestr += command.params[1][j];
						argstr += command.params[argi - 1] + " ";
						break;
					case Channel::MODE_INVITE_ONLY:
					case Channel::MODE_TOPIC_PROTECTED:
						if(channel->unsetMode(r))
							modestr += command.params[1][j];
						break;
					case Channel::MODE_LIMIT_USERS:
						if(channel->unsetUserLimit())
							modestr += command.params[1][j];
						break;
					case Channel::MODE_KEY_REQUIRED:
						if(channel->unsetMode(r))
							modestr += command.params[1][j];
						break;
					}
				}
			}
			i = j;
		}
		// send a message if there were any unknown modes
		if(unknown)
			client->send("501 " + client->nick() + " :Unknown MODE flag\r\n");
		// send a MODE message if there were any modes changed
		if(modestr.find_first_not_of("+-") != std::string::npos)
		{
			channel->sendChannelMessage(client, ":" + client->nick() + " MODE " + channel->getChannelName() + " " + modestr + " " + argstr + "\r\n");
			client->send(":" + Server::host() + " MODE " + channel->getChannelName() + " " + modestr + " " + argstr + "\r\n");
		}

		return true;
	}

	bool mode(const Command& command, Client* client)
	{
		if(command.params.size() < 2)
			return false;

		const std::string channelPrefixes = "#&+!";
		if(channelPrefixes.find(command.params[0][0]) == std::string::npos)
		{ // if the first parameter is not a channel, it's a user
			Client* target = Server::client(command.params[0]);
			if(!target)
			{ // find the user and check if it exists
				client->send("ERROR :No such nick\r\n");
				return false;
			}
			if(!target->isoper() && target != client)
			{ // only oper can change other clients' modes
				client->send("481 " + client->nick() + " :Permission Denied- You're not an IRC operator\r\n");
				return false;
			}
			// parse the modes
			size_t i = 0;
			if(command.params[1][0] != '+' && command.params[1][0] != '-')
				return false;
			std::string modestr;
			bool unknown = false;
			bool perm = false;
			while(i < command.params[1].size())
			{
				size_t j;
				modestr += command.params[1][i];
				for(j = i + 1; command.params[1][j] && command.params[1][j] != '+' && command.params[1][j] != '-'; ++j)
				{
					int r = parseMode(command.params[1][j]);
					if(r == Client::MODE_O && !client->isoper())
						perm = true;
					else if(r == Client::MODE_UNKNOWN)
						unknown = true;
					else if(command.params[1][i] == '+' && client->addmode(r))
						modestr += command.params[1][j];
					else if(client->delmode(r))
						modestr += command.params[1][j];
				}
				i = j;
			}
			// send a message if there were any unknown modes or permission error
			if(perm)
				client->send("481 " + client->nick() + " :Permission Denied- You're not an IRC operator\r\n");
			if(unknown)
				client->send("501 " + client->nick() + " :Unknown MODE flag\r\n");
			// send a MODE message if there were any modes changed
			if(modestr.find_first_not_of("+-") != std::string::npos)
			{
				target->send(client->prefix() + " MODE " + target->nick() + " " + modestr + "\r\n");
				if(target != client)
					client->send(client->prefix() + " MODE " + target->nick() + " " + modestr + "\r\n");
			}

			return true;
		}
		else
			return chanMode(command, client);
	}

	bool join(const Command& command, Client* client)
	{
		if(command.params.size() < 1)
			return false;
		// check if the channel name is valid
		const std::string channelPrefixes = "#&+!";
		if(command.params[0].size() <= 1 || channelPrefixes.find(command.params[0][0]) == std::string::npos)
		{
			client->send("ERROR :Invalid channel name\r\n");
			return false;
		}
		bool created = false;
		// check if the channel exists
		Channel* channel = Server::channel(command.params[0]);
		if(!channel)
		{
			channel = Server::createChannel(command.params[0], client);
			if(!channel)
			{
				client->send("ERROR :Channel creation failed\r\n");
				return false;
			}
			created = true;
		}
		if(command.params.size() > 1)
		{
			if(!channel->addUser(client, command.params[1]))
				return false;
		}
		else
			if(!channel->addUser(client))
				return false;
		
		channel->sendChannelCommand(0, client->prefix() + " JOIN :" + channel->getChannelName() + "\r\n");
		channel->sendUserList(client);
		if(created)
			channel->sendChannelCommand(0, client->prefix() + " MODE " + channel->getChannelName() + " +o " + client->nick() + "\r\n");
		return true;
	}

	bool kick(const Command& command, Client* client)
	{
		if(command.params.size() < 2)
			return false;
		// check if the channel exists
		Channel* channel = Server::channel(command.params[0]);
		if(!channel)
		{
			client->send("ERROR :No such channel\r\n");
			return false;
		}
		if(!client->isoper())
		{
			if(!channel->isUserInChannel(client))
			{
				client->send("ERROR :You're not in that channel\r\n");
				return false;
			}
			if(!channel->isUserChannelOperator(client))
			{
				client->send("ERROR :You're not a channel operator\r\n");
				return false;
			}
		}
		// check if the user exists
		Client* target = Server::client(command.params[1]);
		if(!target)
		{
			client->send("ERROR :No such nick\r\n");
			return false;
		}
		if(!channel->isUserInChannel(target))
		{
			client->send("ERROR :User is not in that channel\r\n");
			return false;
		}
		// kick the user
		if(command.params.size() > 2)
			channel->sendChannelCommand(0, client->prefix() + " KICK " + channel->getChannelName() + " " + target->nick() + " :" + command.params[2] + "\r\n");
		else
			channel->sendChannelCommand(0, client->prefix() + " KICK " + channel->getChannelName() + " " + target->nick() + "\r\n");
		channel->removeUser(target);
		return true;
	}

	bool invite(const Command& command, Client* client)
	{
		if(command.params.size() < 2)
			return false;
		// check if the channel exists
		Channel* channel = Server::channel(command.params[1]);
		if(!channel)
		{
			client->send("ERROR :No such channel\r\n");
			return false;
		}
		if(!client->isoper())
		{
			if(!channel->isUserInChannel(client))
			{
				client->send("ERROR :You're not in that channel\r\n");
				return false;
			}
			if(!channel->isUserChannelOperator(client))
			{
				client->send("ERROR :You're not a channel operator\r\n");
				return false;
			}
		}
		// check if the user exists
		Client* target = Server::client(command.params[0]);
		if(!target)
		{
			client->send("ERROR :No such nick\r\n");
			return false;
		}
		if(channel->isUserInChannel(target))
		{
			client->send("ERROR :User is already in that channel\r\n");
			return false;
		}
		// invite the user
		channel->inviteUser(client, target);
		return true;
	}

	bool topic(const Command& command, Client* client)
	{
		if(command.params.size() < 1)
			return false;
		// check if the channel exists
		Channel* channel = Server::channel(command.params[0]);
		if(!channel)
		{
			client->send("ERROR :No such channel\r\n");
			return false;
		}
		if(!client->isoper())
		{
			if(!channel->isUserInChannel(client))
			{
				client->send("ERROR :You're not in that channel\r\n");
				return false;
			}
			if(!channel->isUserChannelOperator(client) && command.params.size() > 1 && channel->getMode(Channel::MODE_TOPIC_PROTECTED))
			{
				client->send("ERROR :You're not a channel operator\r\n");
				return false;
			}
		}
		// set the topic
		if(command.params.size() > 1)
			channel->setTopic(client, command.params[1]);
		else
			channel->getTopic(client);
		return true;
	}

	bool part(const Command& command, Client* client)
	{
		if(command.params.size() < 1)
			return false;
		// check if the channel exists
		Channel* channel = Server::channel(command.params[0]);
		if(!channel)
		{
			client->send("ERROR :No such channel\r\n");
			return false;
		}
		if(!channel->isUserInChannel(client))
		{
			client->send("ERROR :You're not in that channel\r\n");
			return false;
		}
		// part the channel
		if(command.params.size() > 1)
			channel->sendChannelCommand(0, client->prefix() + " PART " + channel->getChannelName() + " :" + command.params[1] + "\r\n");
		else
			channel->sendChannelCommand(0, client->prefix() + " PART " + channel->getChannelName() + "\r\n");
		channel->removeUser(client);
		return true;
	}
}
