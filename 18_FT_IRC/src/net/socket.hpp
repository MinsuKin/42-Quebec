#pragma once

//#include <netinet/in.h>
#include <sys/socket.h>

#include "net.hpp"
#include "common.hpp"

namespace net
{
	class Socket
	{
	public:
		Socket();
		Socket(sockettype type);

		~Socket();

		operator const int&() const { return _sockfd; }

		// True if socket was created and not closed
		bool valid() const { return _sockfd != -1; }
		bool bound() const { return _bound; }
		bool connected() const { return _connected; }

		bool create(sockettype type);
		bool bind(in_addr addr, uint16 port);
//		bool bind(in6_addr addr, uint16 port) const;
		bool send(const char* data, uint32 size) const;
		ssize_t receive(void* data, uint32 size);
		bool listen(uint32 backlog);
		bool accept(const Socket& as);
		void close();

	private:
		Socket(const Socket&); // Copy
		Socket& operator=(const Socket&);

		template<typename T>
		void setoption(int option, int level, T value) const { setsockopt(_sockfd, level, option, reinterpret_cast<void*>(&value), sizeof(T)); }

		int _sockfd;

		bool _bound;
		bool _connected;
	};
}
