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
#include "network.h"

void Descent_atoinet(const string &input, struct sockaddr_in &addr) {
#ifdef _WIN32
	long inAddress;
	inAddress = inet_addr(input.c_str());
	addr.sin_addr.s_addr = inAddress;
#else
   inet_aton(input.c_str(), (struct in_addr *)&addr.sin_addr.s_addr);
#endif
}