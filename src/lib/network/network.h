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
#ifndef SRC_LIB_NETWORK_NETWORK_H_
#define SRC_LIB_NETWORK_NETWORK_H_

#ifdef _WIN32
#include <WinSock2.h>

typedef SOCKET Descent_Socket;
typedef int socklen_t;

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

typedef int Descent_Socket;

#endif

#include <string>

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace NETWORK {

typedef struct INetwork {
  virtual Descent_Socket socket(int domain, int type, int protocol) = 0;
  virtual int close(Descent_Socket socket) = 0;
  virtual void atoinet(const ::std::string &input,
                       struct sockaddr_in &addr) = 0;
  virtual struct protoent *getprotobyname(const char *name) = 0;
  virtual int setsockopt(Descent_Socket sockfd, int level, int optname,
                         const void *optval, socklen_t optlen) = 0;
  virtual ssize_t recvfrom(Descent_Socket sockfd, void *buf, size_t len,
                           int flags, struct sockaddr *src_addr,
                           socklen_t *addrlen) = 0;
  virtual int bind(Descent_Socket sockfd, const struct sockaddr *addr,
                   socklen_t addrlen) = 0;
  virtual int select(int nfds, fd_set *readfds, fd_set *writefds,
                     fd_set *exceptfds, struct timeval *timeout) = 0;
} INetwork;

class CNetwork : INetwork {
 public:
  static INetwork &get_Instance();

  virtual Descent_Socket socket(int domain, int type, int protocol);
  virtual int close(Descent_Socket socket);
  virtual void atoinet(const ::std::string &input, struct sockaddr_in &addr);
  virtual struct protoent *getprotobyname(const char *name);
  virtual int setsockopt(Descent_Socket sockfd, int level, int optname,
                         const void *optval, socklen_t optlen);
  virtual ssize_t recvfrom(Descent_Socket sockfd, void *buf, size_t len,
                           int flags, struct sockaddr *src_addr,
                           socklen_t *addrlen);
  virtual int bind(Descent_Socket sockfd, const struct sockaddr *addr,
                   socklen_t addrlen);
  virtual int select(int nfds, fd_set *readfds, fd_set *writefds,
                     fd_set *exceptfds, struct timeval *timeout);

 private:
  static CNetwork mSingleton;
  CNetwork();
  CNetwork(const CNetwork &source);
  ~CNetwork();
  CNetwork &operator=(const CNetwork &source);
};

}  // namespace NETWORK
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT

#endif  // SRC_LIB_NETWORK_NETWORK_H_
