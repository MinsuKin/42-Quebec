#include "server.hpp"

#include <iostream>
#include <netdb.h>

const std::string Server::VERSION = "0.1";
const std::string Server::NAME = "supercoolircserver";
time_t Server::_currenttime = 0;
uint16 Server::_port = 8080;
std::string Server::_password;
std::string Server::_host = "supercoolircserver.irc";
const std::string Server::_oppassword = "oppass";
net::Socket Server::_asocket;
Client* Server::_newclient = 0;
std::vector<Client*> Server::_clients;
std::vector<pollfd> Server::_pollfds;
std::vector<Channel*> Server::_channels;

const uint32 Server::_QUEUE_SIZE = 64;

Server::Server()
{
}

Server::Server(const Server& obj)
{
	(void)obj; // nuh uh
}

Server::~Server()
{
	shutdown();
}

bool Server::init(uint16 port, const char* password)
{
	_port = port;
	_password = password;
	_clients.reserve(16);
	_pollfds.reserve(16);
	if(!_asocket.create(net::tcp))
	{
		std::cerr << "Failed to open accepting socket" << std::endl;
		return false;
	}
	const in_addr addr = INITADDR;
	if(!_asocket.bind(addr, _port))
	{
		std::cerr << "Failed to bind accepting socket to port 8080" << std::endl;
		return false;
	}
	if(!_asocket.listen(_QUEUE_SIZE))
	{
		std::cerr << "Failed to enable listen queue on accepting socket" << std::endl;
		return false;
	}
	pollfd pfd;
	pfd.fd = _asocket;
	pfd.events = POLLIN;
	pfd.revents = 0;
	_pollfds.push_back(pfd);
	_clients.push_back(0); // dummy client to align indices
	return true;
}

bool Server::run()
{
	_newclient = new Client();
	while(true)
	{
		int r;
		if((r = poll(_pollfds.data(), _pollfds.size(), 1000)) < 0 || _pollfds[0].revents & (POLLERR | POLLNVAL))
			return false;

		_currenttime = std::time(NULL); // we only need to update this once per loop

		checkTimeouts();

		// if poll times out it returns 0, we don't need to check for any events in that case
		if(r)
		{
			if(_pollfds[0].revents & POLLIN)
				accept();

			for(uint64 i = 1; i < _pollfds.size(); ++i)
				if(_pollfds[i].revents & POLLIN)
					if(_pollfds[i].revents & POLLHUP || !receive(i))
						_clients[i]->flagDisconnect = true;

			for(uint64 i = 1; i < _clients.size(); ++i)
				if(_clients[i]->flagDisconnect)
					disconnect(i--);
		}
	}
	return false;
}

bool Server::accept()
{
	if(_newclient->accept(_asocket))
	{
		_clients.push_back(_newclient);
		pollfd pfd;
		pfd.fd = *_newclient;
		pfd.events = POLLIN;
		pfd.revents = 0;
		_pollfds.push_back(pfd);
		_newclient = new Client();
		return true;
	}
	std::cerr << "Failed to accept client" << std::endl;
	return false;
}

bool Server::receive(uint64 id)
{
	if(!_clients[id]->receive())
		return false;
	return true;
}

void Server::disconnect(uint64 id)
{
	receive(id); // receive any remaining data
	delete _clients[id];
	_clients.erase(_clients.begin() + id);
	_pollfds.erase(_pollfds.begin() + id);
}

Channel* Server::channel(const std::string& name)
{
	for(uint64 i = 0; i < _channels.size(); ++i)
		if(_channels[i]->getChannelName() == name)
			return _channels[i];
	return 0;
}

Channel* Server::createChannel(const std::string& name, Client* user)
{
	Channel* c = new Channel(name, user);
	_channels.push_back(c);
	return c;
}

bool Server::broadcast(const std::string& data, const Client* except)
{
	for(uint64 i = 1; i < _clients.size(); ++i)
		if(_clients[i] != except && !_clients[i]->send(data.c_str(), data.size()))
			return false;
	return true;
}
bool Server::broadcast(const std::string& data, const std::string& except)
{
	for(uint64 i = 1; i < _clients.size(); ++i)
		if(_clients[i]->nick() != except && !_clients[i]->send(data.c_str(), data.size()))
			return false;
	return true;
}

bool Server::send(const std::string& data, const Client* client)
{
	return client->send(data.c_str(), data.size());
}
bool Server::send(const std::string& data, const std::string& client)
{
	const Client* const c = Server::client(client);
	if(c)
		return c->send(data.c_str(), data.size());
	return false;
}

Client* Server::client(const std::string& nick)
{
	for(uint64 i = 1; i < _clients.size(); ++i)
		if(_clients[i]->nick() == nick)
			return _clients[i];
	return 0;
}

Client* Server::client(uint64 id)
{
	return _clients[id];
}

void Server::shutdown()
{
	std::cout << "Server shutdown" << std::endl;
	delete _newclient;
	_newclient = 0;
	for(uint64 i = 1; i < _clients.size(); ++i)
		delete _clients[i];
	for(uint64 i = 0; i < _channels.size(); ++i)
		delete _channels[i];
	_clients.clear();
}

bool Server::sendUserList(const Client* client)
{
	std::string msg = ":" + Server::NAME + " 353 " + client->nick() + " = " + client->nick() + " :";
	for(uint64 i = 1; i < _clients.size(); ++i)
	{
		msg += _clients[i]->nick();
		msg += " ";
	}
	msg += "\r\n";
	return client->send(msg.c_str(), msg.size());
}

void Server::checkTimeouts()
{
	for(uint64 i = 1; i < _clients.size(); ++i)
	{
		if(_currenttime - _clients[i]->lastping() > 70 && _clients[i]->lastpinged() <= _clients[i]->lastping())
			_clients[i]->ping();
		else if(_currenttime - _clients[i]->lastping() > 120)
			_clients[i]->flagDisconnect = true;
	}
}
