#pragma once

#include <vector>
#include <string>
#include <poll.h>

#include "common.hpp"
#include "net/net.hpp"
#include "client.hpp"
#include "channel.hpp"

class Server
{
public:
	Server();
	~Server();

	static bool init(uint16 port, const char* password);
	static bool run();
	static void shutdown();

	static bool accept();
	static bool receive(uint64 id);
	static void disconnect(uint64 id);

	static Channel* channel(const std::string& name);
	static Channel* createChannel(const std::string& name, Client* user);

	static bool broadcast(const std::string& data, const Client* except = 0);
	static bool broadcast(const std::string& data, const std::string& except);
	static bool send(const std::string& data, const Client* client);
	static bool send(const std::string& data, const std::string& client);

	static Client* client(const std::string& nick);
	static Client* client(uint64 index);
	static size_t clientCount() { return _clients.size() - 1; }

	static void checkTimeouts();

	static time_t currenttime() { return _currenttime; }

	static uint16 port() { return _port; }
	static const std::string& host() { return _host; }
	static const std::string& password() { return _password; }
	static const std::string& oppassword() { return _oppassword; }

	static bool sendUserList(const Client* client);

	static const std::string VERSION;
	static const std::string NAME;

private:
	Server(const Server& obj);
	Server& operator=(const Server& obj);

	static time_t _currenttime;

	static uint16 _port;
	static std::string _host;
	static std::string _password;
	static const std::string _oppassword;

	static net::Socket _asocket;
	static Client* _newclient;
	static std::vector<Client*> _clients;
	static std::vector<pollfd> _pollfds;

	static std::vector<Channel*> _channels;

	static const uint32 _QUEUE_SIZE;
};
