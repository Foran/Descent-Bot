#include "connectionmanager.h"

int CConnectionManager::mReferences = 0;
int CConnectionManager::mSocket = -1;
vector<CConnection *> CConnectionManager::mConnections;

CConnectionManager::CConnectionManager()
{
   if(0 == mReferences++) {
      mSocket = socket(PF_INET, SOCK_DGRAM, getprotobyname("udp")->p_proto);
      if(mSocket != -1) {
	 int on = 1;
	 setsockopt(mSocket, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
	 struct sockaddr_in addr;
	 memset(&addr, 0, sizeof(addr));
	 addr.sin_family = AF_INET;
	 addr.sin_port = htons(42424);
	 addr.sin_addr.s_addr = INADDR_ANY;
	 bind(mSocket, (struct sockaddr *)&addr, sizeof(addr));
      }
   }
}

CConnectionManager::CConnectionManager(const CConnectionManager &source)
{
   *this = source;
}

CConnectionManager::~CConnectionManager()
{
   if(--mReferences) {
      for(vector<CConnection *>::iterator i = mConnections.begin(); i != mConnections.end(); i++) {
	 delete *i;
      }
      mConnections.clear();
      if(mSocket >= 0) {
	 close(mSocket);
	 mSocket = -1;
      }
   }
}

CConnectionManager &CConnectionManager::operator=(const CConnectionManager &source)
{
   mReferences++;
   return *this;
}

CConnectionManager CConnectionManager::get_Instance()
{
   return CConnectionManager();
}
