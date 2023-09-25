#pragma once

#include "client.hpp"

#include <iostream>
#include <vector>

class Channel
{
public:
	Channel(std::string channelName, Client* user);
	~Channel() {}

	static const char* const CHANMODES;

	enum
	{
		MODE_INVITE_ONLY = 1 << 0,
		MODE_TOPIC_PROTECTED = 1 << 1,
		MODE_LIMIT_USERS = 1 << 2,
		MODE_KEY_REQUIRED = 1 << 3,
		MODE_OP = 1 << 4,
		MODE_UNKNOWN = 1 << 5
	};

	const std::string& getChannelName() const { return _channelName; }
	const std::vector<Client*>& getUserList() const { return _userList; }
	const std::vector<Client*>& getChannelOperators() const { return _channelOperators; }
	const std::string& getCurrentTopic() const { return _topic; } // TOPIC #channelName
	
	bool isUserInChannel(Client* user) const;
	bool addUser(Client* user, std::string key = ""); // JOIN
	bool removeUser(Client* user); // PART

	bool isUserChannelOperator(Client* user) const;
	bool addChannelOperator(Client* op, Client* userTarget); // MODE +o
	bool removeChannelOperator(Client* userTarget); // MODE -o

	bool setTopic(Client* user, std::string topic); // TOPIC #channelName :topic
	bool getTopic(Client* user) const;
	bool sendChannelMessage(Client* user, std::string message); // PRIVMSG #channelName :message
	bool sendChannelCommand(Client* user, std::string command); // sends message without any prefix or changes

	bool inviteUser(Client* op, Client* userTarget); // INVITE user #channelName

	bool setMode(int mode) { if(_modes & mode) return false; _modes |= mode; return true; }
	bool unsetMode(int mode) { if(!(_modes & mode)) return false; _modes &= ~mode; return true; }
	bool getMode(int mode) { return _modes & mode; }

	bool setUserLimit(const std::string& limit);
	bool unsetUserLimit() { if(_maxUsers == 0) return false; _maxUsers = 0; _modes &= ~MODE_LIMIT_USERS; return true; }
	bool setKey(const std::string& key) { if(_modes & MODE_KEY_REQUIRED) return false; _key = key; _modes |= MODE_KEY_REQUIRED; return true;}
	bool unsetKey() { if(!(_modes & MODE_KEY_REQUIRED)) return false; _key.clear(); _modes &= ~MODE_KEY_REQUIRED; return true; }

	bool sendUserList(Client* user) const; // RPL_NAMREPLY

private:

	std::string _channelName;
	std::vector<Client*> _userList;
	std::vector<Client*> _channelOperators; // _channelOperators[0] is the channel creator
	std::vector<Client*> _invitedUserList;

	int _modes; // bit field

	size_t _maxUsers;
	std::string _topic;
	std::string _topicUser;
	time_t _topicTime;
	std::string _key;
};
