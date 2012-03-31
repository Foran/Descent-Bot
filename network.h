/****************************************************
 * This work is licensed under the Creative
 * Commons Attribution-NonCommercial-ShareAlike
 * 3.0 Unported License. To view a copy of this
 * license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * or send a letter to Creative Commons, 444
 * Castro Street, Suite 900, Mountain View,
 * California, 94041, USA.
 ***************************************************/
#ifndef __NETWORK_H__

#ifdef _WIN32
#include <WinSock2.h>

typedef SOCKET Descent_Socket;
typedef int socklen_t;

#define Descent_CloseSocket(socket) closesocket(socket)

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

typedef int Descent_Socket;

#define Descent_CloseSocket(socket) close(socket)

#endif

#include<string>

using namespace std;

extern void Descent_atoinet(const string &input, struct sockaddr_in &addr);

#endif
