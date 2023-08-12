//
//  Utils.h
//  ipc
//
//  Created by Yuriy Belikov on 11.01.2021.
//

#ifndef Utils_h
#define Utils_h
#include <sys/types.h>
#include "Socket.h"

namespace Utils
{
	int SendMessageLength(const Socket* socket, ssize_t messageLength);
	int ReceiveMessageLength(const Socket* socket, ssize_t& messageLength);
};

#endif /* Utils_h */
