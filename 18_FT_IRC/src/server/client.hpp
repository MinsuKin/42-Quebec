#pragma once

#include "net/socket.hpp"

#include <string>
#include <ctime>

class Client
{
public:
	Client();
	~Client();

	static const char* const USERMODES;

	enum
	{
		MODE_I = 1 << 0,
		MODE_O = 1 << 1,
		MODE_S = 1 << 2,
		MODE_V = 1 << 3,
		MODE_COUNT = 4,
		USER_REGISTERED = 1 << 4,
		USER_PASSWORDED = 1 << 5,
		MODE_UNKNOWN = 1 << 6
	};

	operator const int&() const { return _socket; }

	bool accept(const net::Socket& s);
	bool receive();
	bool send(const char* string) const;
	bool send(const char* data, uint32 size) const;
	bool send(const std::string& data) const;
	bool ping();
	// bool sendmodes(const std::string& added, const std::string& removed) const;

	const std::string& data() const { return _data; }

	bool password(const std::string& pass);
	bool setnick(const std::string& nick);
	bool setuser(const std::string& user, const std::string& realname);
	bool oper(const std::string& user, const std::string& pass);
	bool addmode(int mode) { if(_modes & mode) return false; _modes |= mode; return true; }
	bool delmode(int mode) { if(!(_modes & mode)) return false; _modes &= ~mode; return true; }
	int modes() const { return _modes; }

	const std::string& nick() const { return _nick; }
	const std::string& user() const { return _user; }
	const std::string& realname() const { return _realname; }

	std::string prefix() const;

	bool passworded() const { return _modes & USER_PASSWORDED; }
	bool registered() const { return _modes & USER_REGISTERED; }
	bool isoper() const { return _modes & MODE_O; }

	std::time_t lastping() const { return _lastping; }
	std::time_t lastpinged() const { return _lastpinged; }

	bool flagDisconnect;

private:

	Client(const Client& obj);
	Client& operator=(const Client& obj);

	std::time_t _lastping;
	std::time_t _lastpinged;

	std::string _nick;
	std::string _user;
	std::string _realname;

	std::string _data;

	int _modes; // bit field

	net::Socket _socket;
};
