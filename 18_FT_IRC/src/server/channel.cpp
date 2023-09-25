#include "channel.hpp"

#include "server.hpp"

#include <sstream>

const char* const Channel::CHANMODES = "itlko";

Channel::Channel(std::string channelName, Client* user)
{
	_channelName = channelName;
	_channelOperators.push_back(user);
	_topic = "";
	_modes = 0;
}

bool Channel::addUser(Client* user, std::string key)
{
	if(isUserInChannel(user))
		return false;
	// if invite-only mode
	if(_modes & MODE_INVITE_ONLY)
	{
		for(std::vector<Client*>::iterator it = _invitedUserList.begin(); it != _invitedUserList.end(); ++it)
		{
			if(*it == user)
			{
				_userList.push_back(user);
				return true;
			}
		}
		return false;
	}
	// if key-required mode
	if(_modes & MODE_KEY_REQUIRED && _key != key)
		return false;
	// if limit-user mode
	if(_modes & MODE_LIMIT_USERS && _userList.size() >= _maxUsers) // _maxUsers = 0 shouln't happen when setting the mode
		return false;
	_userList.push_back(user);
	return true;
}

bool Channel::removeUser(Client* user)
{
	removeChannelOperator(user);
	for(std::vector<Client*>::iterator it = _userList.begin(); it != _userList.end(); ++it)
	{
		if(*it == user)
		{
			_userList.erase(it);
			return true;
		}
	}
	return false;
}

bool Channel::isUserInChannel(Client* user) const
{
	for(std::vector<Client*>::const_iterator it = _userList.begin(); it != _userList.end(); ++it)
		if(*it == user)
			return true;
	return false;
}

bool Channel::isUserChannelOperator(Client* user) const
{
	for(std::vector<Client*>::const_iterator it = _channelOperators.begin(); it != _channelOperators.end(); ++it)
	{
		if(*it == user)
			return true;
	}
	return false;
}

bool Channel::addChannelOperator(Client* op, Client* userTarget)
{
	if(!userTarget || isUserChannelOperator(userTarget) ||(!op->isoper() && (!isUserInChannel(userTarget) || !isUserChannelOperator(op))))
		return false;
	_channelOperators.push_back(userTarget);
	return true;
}

bool Channel::removeChannelOperator(Client* userTarget)
{
	if(!userTarget)
		return false;
	for(std::vector<Client*>::iterator it = _channelOperators.begin(); it != _channelOperators.end(); ++it)
	{
		if(*it == userTarget)
		{
			_channelOperators.erase(it);
			return true;
		}
	}
	return false;
}

bool Channel::setTopic(Client* user, std::string topic)
{
	if(!user->isoper() && (_modes & MODE_TOPIC_PROTECTED && !isUserChannelOperator(user)))
		return false;
	_topic = topic;
	_topicUser = user->nick();
	_topicTime = Server::currenttime();
	sendChannelCommand(0, user->prefix() + " TOPIC " + _channelName + " :" + topic + "\r\n");
	return true;
}

bool Channel::getTopic(Client* user) const
{
	if(_topic == "")
	{
		user->send(":" + Server::host() + " 331 " + user->nick() + " " + _channelName + " :No topic is set\r\n");
		return true;
	}
	std::stringstream ss;
	ss << _topicTime;
	user->send(":" + Server::host() + " 332 " + user->nick() + " " + _channelName + " :" + _topic + "\r\n");
	user->send(":" + Server::host() + " 333 " + user->nick() + " " + _channelName + " " + _topicUser + " :" + ss.str() + "\r\n");
	return true;
}

bool Channel::sendChannelMessage(Client* user, std::string message)
{
	for(std::vector<Client*>::iterator it = _userList.begin(); it != _userList.end(); ++it)
		if(*it != user)
			(*it)->send(user->prefix() + " PRIVMSG " + _channelName + " :" + message + "\r\n");
	return true;
}

bool Channel::sendChannelCommand(Client* user, std::string command)
{
	for(std::vector<Client*>::iterator it = _userList.begin(); it != _userList.end(); ++it)
		if(*it != user)
			(*it)->send(command);
	return true;
}

bool Channel::inviteUser(Client* op, Client* userTarget)
{
	if(!op->isoper() && (!isUserChannelOperator(op) || isUserInChannel(userTarget)))
		return false;
	if(_modes & MODE_INVITE_ONLY)
		_invitedUserList.push_back(userTarget);
	userTarget->send(op->prefix() + " INVITE " + userTarget->nick() + " :" + _channelName + "\r\n");
	return true;
}

bool Channel::setUserLimit(const std::string& limit)
{
	if(_modes & MODE_LIMIT_USERS)
		return false;
	std::stringstream ss(limit);
	ss >> _maxUsers;
	if(ss.fail() || !ss.eof())
	{
		_maxUsers = 0;
		return false;
	}
	_modes |= MODE_LIMIT_USERS;
	return true;
}

bool Channel::sendUserList(Client* user) const
{
	std::string userList;
	for(std::vector<Client*>::const_iterator it = _userList.begin(); it != _userList.end(); ++it)
	{
		if((*it)->modes() & Client::MODE_I)
			continue; // invisible user
		if(it != _userList.begin())
			userList += " ";
		if(isUserChannelOperator(*it))
			userList += "@";
		userList += (*it)->nick();
	}
	user->send(":" + Server::host() + " 353 " + user->nick() + " @ " + _channelName + " :" + userList + "\r\n");
	user->send(":" + Server::host() + " 366 " + user->nick() + " " + _channelName + " :End of /NAMES list.\r\n");
	return true;
}
