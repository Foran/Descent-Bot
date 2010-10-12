#ifndef __HOG_H__
#define __HOG_H__

#include <string>
#include <vector>
#include <map>

using namespace std;

class CHog {
	public:
		CHog();
		CHog(const string &filename);
		CHog(const CHog &source);

		~CHog();

		CHog &operator=(const CHog &source);
	protected:
	private:
};

#endif

