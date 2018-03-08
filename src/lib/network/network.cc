/****************************************************
 * Copyright 2018 Ben M. Ward
 *
 * This work is licensed under the Creative
 * Commons Attribution-NonCommercial-ShareAlike
 * 3.0 Unported License. To view a copy of this
 * license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * or send a letter to Creative Commons, 444
 * Castro Street, Suite 900, Mountain View,
 * California, 94041, USA.
 ***************************************************/
#include "src/lib/network/network.h"

using ::std::string;

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace NETWORK {

CNetwork CNetwork::mSingleton;

INetwork &CNetwork::get_Instance() {
  return mSingleton;
}

CNetwork::CNetwork() {
}

CNetwork::~CNetwork() {
}

Descent_Socket CNetwork::socket(int domain, int type, int protocol) {
  return (Descent_Socket)::socket(domain, type, protocol);
}

int CNetwork::close(Descent_Socket socket) {
   int retval = 0;
#ifdef _WIN32
   retval = closesocket(socket);
#else
   retval = ::close(socket);
#endif
   return retval;
}

void CNetwork::atoinet(const string &input, struct sockaddr_in &addr) {
#ifdef _WIN32
   long inAddress;
   inAddress = inet_addr(input.c_str());
   addr.sin_addr.s_addr = inAddress;
#else
   inet_aton(input.c_str(), (struct in_addr *)&addr.sin_addr.s_addr);
#endif
}

struct protoent *CNetwork::getprotobyname(const char *name) {
  return ::getprotobyname(name);
}

int CNetwork::setsockopt(Descent_Socket sockfd, int level, int optname, const void *optval, socklen_t optlen) {
  return ::setsockopt(sockfd, level, optname, optval, optlen);
}

ssize_t CNetwork::recvfrom(Descent_Socket sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen) {
  return ::recvfrom(sockfd, buf, len, flags, src_addr, addrlen);
}

int CNetwork::bind(Descent_Socket sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  return ::bind(sockfd, addr, addrlen);
}

int CNetwork::select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) {
  return ::select(nfds, readfds, writefds, exceptfds, timeout);
}

}  // namespace NETWORK
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT
