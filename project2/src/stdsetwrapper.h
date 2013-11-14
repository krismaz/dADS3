#ifndef STDSETWRAPPER_H
#define STDSETWRAPPER_H

#include <set>

class StdSetWrapper
{
private:
	std::set<unsigned int> set;
public:
	void Insert(unsigned int x)
	{
		set.insert(x);
	}

	void Delete(unsigned int x)
	{
		set.erase(x);
	}

	unsigned int Predecessor(unsigned int x)
	{
		if(set.empty())
		{
			return -1;
		}
		auto it = set.lower_bound(x);
		if(it == set.begin())
		{
			return -1;
		}
		return *(--it);
	}

	unsigned int Min() {
		auto derp = set.begin();
		return (*derp);
	}
};

#endif