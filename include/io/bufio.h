#ifndef _BUFIO_
#define _BUFIO_

#include <stddef.h>

#include "../datastruct/quene.h"

namespace myclone
{
	class BufOut
	{
		int _handle;

		data::quene _buf;

		size_t _blksize;
		size_t _min_blksize;

		void _blkwrite();
	public:
		BufOut(const char *filename);

 		int write(const char *buf, const int size);
		
		~BufOut();
	};
};

#endif //_BUFIO_
