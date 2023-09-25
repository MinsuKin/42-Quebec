#include "net.hpp"

//#include <sys/socket.h>

namespace net
{
	const int ADDRFAMILIES[] =
		{
			0,      // invalid
			AF_INET, // ipv4
			AF_UNSPEC // all
		};

	const socklen_t SOCKSIZES[] =
		{
			0,
			sizeof(sockaddr_in), // ipv4
			sizeof(sockaddr_in6) // ipv6
		};

	const int SOCKTYPES[] =
		{
			0,          // none
			SOCK_STREAM // tcp
		};
}
