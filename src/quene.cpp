#include "../include/datastruct/quene.h"

#include <cstring>

data::quene::quene(const size_t increase) : __INCREASE(increase)
{
	__buf = nullptr;
	__szbuf = 0;

	__front = 0;
	__pare = 0;
}

void data::quene::push(const char *buf, const size_t szbuf)
{
	if (__szbuf - size() < szbuf)
		__inflate(szbuf);
	
	for (size_t i = 0; i < szbuf; i++)
		__push_char(buf[i]);

}

char *data::quene::pop(const size_t szbuf)
{
	if (size() < szbuf)
		return nullptr;
	
	char *ret = new char[szbuf];
	for (size_t i = 0; i < szbuf; i++)
		ret[i] = __pop_char();

	return ret;
}

size_t data::quene::size()
{
	return (__pare - __front < 0) ? -(__pare - __front) : __pare - __front;
}

void data::quene::__inflate(const int nwsize)
{
	if (__buf == nullptr)
		__buf = new char[nwsize];

	char *nwbuf = new char[nwsize];
	std::memcpy(nwbuf, __buf, __szbuf);

	delete[] __buf;

	__szbuf = nwsize;
	__buf = nwbuf;
}

data::quene::~quene()
{
	delete[] __buf;
}
