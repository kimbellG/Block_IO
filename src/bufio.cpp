#include "../include/io/bufio.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

myclone::BufOut::BufOut(const char *filename)
{
	_handle = ::open(filename, O_WRONLY | O_CREAT, 0644);
	
	struct ::stat buf;
	::stat(filename, &buf);

	_blksize = buf.st_blksize;
	if (_blksize > 16)
		_min_blksize = _blksize >> 2;
	else 
		_min_blksize = _blksize;
	
#ifdef DEBUG
	std::cout << "[DEBUG] Creating bufout: " << std::endl
		      << "\tfilename = " << filename << std::endl
			  << "\thandle = " << _handle << std::endl
			  << "\t_blksize = " << _blksize << std::endl
			  << "\t_min_blksize = " << _min_blksize << std::endl;
#endif //DEBUG
}	

int myclone::BufOut::write(const char *buf, const int size)
{


	_buf.push(buf, size);

	if (_buf.size() > _min_blksize)
		_blkwrite();

	return size;
}

void myclone::BufOut::_blkwrite()
{
	size_t current_blksize = _blksize;

	while (_buf.size() >= _min_blksize)
	{
#ifdef DEBUG
		std::cout << "[DEBUG] Write block on disk: " << std::endl  
				  << "\t_buf.size() = " << _buf.size() << std::endl;
#endif // DEBUG
		if (_buf.size() > current_blksize)
		{
#ifdef DEBUG
			std::cout << "[DEBUG] _buf.size() > current_blksize == true" << std::endl;
#endif // DEBUG
			char *block = _buf.pop(current_blksize);
			int ret = ::write(_handle, block, current_blksize);
#ifdef DEBUG
			std::cout << "[DEBUG] Writing " << ret << " byte" << std::endl << std::endl;
#endif //DEBUG
			if (ret == -1)
			{
				::perror("_blkwrite::write");
				exit(1);
			}	

			delete[] block;
		} else
#ifdef DEBUG
		{
			std::cout << "[DEBUG] _buf.size() > current_blksize == false" << std::endl
					  << "[DEBUG] modify current_blksize" << std::endl;
			current_blksize = current_blksize >> 1;
			std::cout << "[DEBUG] current_blksize = " << current_blksize << std::endl << std::endl;
		}
#else
			current_blksize = current_blksize >> 1;
#endif //DEBUG

	}	
}	

myclone::BufOut::~BufOut()
{
#ifdef DEBUG
	std::cout << "[DEBUG] Closing file" << std::endl;  
#endif //DEBUG

	if (!_buf.size())
	{
#ifdef DEBUG
		std::cout << "[DEBUG] _buf.size() == 0" << std::endl;
#endif //DEBUG
		::close(_handle);
		return;
	}

#ifdef DEBUG
	std::cout << "[DEBUG] Writing last block" << std::endl
			  << "[DEBUG] _buf.size() = " << _buf.size() << std::endl;
#endif //DEBUG
	int szbuf = _buf.size();
	char *lastblk = _buf.pop(szbuf);

	int ret = ::write(_handle, lastblk, szbuf);

#ifdef DEBUG
	std::cout << "[DEBUG] Writing " << ret << " byte" << std::endl << std::endl;
#endif // DEBUG
	if (ret == -1)
	{
		perror("~BufOut::write");
		exit(1);
	}

	::close(_handle);
	delete[] lastblk;
}
