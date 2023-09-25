#include "client.hpp"

#include "server.hpp"
#include "command.hpp"

#include <iostream>

const char* const Client::USERMODES = "iosv";

Client::Client() : flagDisconnect(false), _lastping(0), _lastpinged(0), _modes(0)
{
}

Client::~Client()
{
}

bool Client::accept(const net::Socket& s)
{
	_lastping = Server::currenttime();
	return _socket.accept(s);
}

bool Client::send(const char* string) const
{
	return _socket.send(string, std::char_traits<char>::length(string));
}

bool Client::send(const char* data, uint32 size) const
{
	return _socket.send(data, size);
}

bool Client::send(const std::string& data) const
{
	return _socket.send(data.c_str(), data.size());
}

bool Client::receive()
{
	_lastping = Server::currenttime();
	char buffer[1024];
	ssize_t r;
	if((r = _socket.receive(buffer, 1023)) < 1)
		return false;

	do // Receive all data
	{
		buffer[r] = '\0';
		_data += buffer;
	} while((r = _socket.receive(buffer, 1023)) > 0);

	size_t pos;
	while((pos = _data.find("\r\n")) != std::string::npos)
	{ // execute all complete commands
		Command::parse(_data.substr(0, pos), this);
		_data.erase(0, pos + 2);
	}

	return true;
}

bool Client::oper(const std::string& user, const std::string& pass)
{
	if(user == _user && pass == Server::oppassword())
	{
		_modes |= MODE_O;
		return true;
	}
	return false;
}

bool Client::ping()
{
	_lastpinged = Server::currenttime();
	std::string msg = "PING " + Server::host() + "\r\n";
	return _socket.send(msg.c_str(), msg.size());
}

bool Client::password(const std::string& pass)
{
	if(pass == Server::password())
		_modes |= USER_PASSWORDED;
	return _modes & USER_PASSWORDED;
}

bool Client::setnick(const std::string& nick)
{
	if(nick.empty() || nick.size() > 9)
		return false;
	_nick = nick;
	return true;
}

bool Client::setuser(const std::string& user, const std::string& realname)
{
	if(user.empty() || realname.empty())
		return false;
	if(user.size() > 9)
		return false;
	
	_user = user;
	_realname = realname;

	_modes |= USER_REGISTERED;
	return true;
}

std::string Client::prefix() const
{
	std::string prefix = ":" + _nick + "!" + _user + "@" + Server::host();
	return prefix;
}
