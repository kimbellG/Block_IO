#ifndef __MY_QUENE__
#define __MY_QUENE__

#include <stddef.h>

namespace data
{
	class quene
	{
		const size_t __INCREASE;	

		char *__buf;
		size_t __szbuf;

		size_t __front;
		size_t __pare;	

		//func
		void __inflate(const int nwsize);
		void __push_char(const char ch)
		{
			if (__pare == __szbuf && __front != 0)
				__pare = 0;

			__buf[__pare++] = ch;
				
		}
		char __pop_char()
		{
			if (__front == __szbuf && __pare != 0)
				__front = 0;
			
			return __buf[__front++];
		}

	public:
		quene(const size_t increase = 4096);

		void push(const char *buf, const size_t size);
		char *pop(const size_t size);

		size_t size();

		~quene();
	};
};

#endif //__MY_QUENE__
