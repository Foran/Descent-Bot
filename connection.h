#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class CConnection 
{
 public:
 protected:
 private:
     CConnection(const CConnection &source);
   CConnection &operator=(const CConnection &source);
};

#endif
