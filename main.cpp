#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <time.h>

#include "io/bufio.h"
#include "datastruct/quene.h"

int main(int argc, char *argv[])
{
	std::string infile;
	std::string outfile;
	std::string str_size;

	int ret = 0;
	while ((ret = ::getopt(argc, argv, "i:o:s:")) != -1)
	{
		switch (ret)
		{
			case 'i':
				infile = ::optarg;
				std::cout << "Input file: " << infile << std::endl;
				break;
			case 'o':
				outfile = ::optarg;
				std::cout << "Output file: " << outfile << std::endl;
				break;
			case 's':
				str_size = ::optarg;
				std::cout << "Size: " << str_size << std::endl;
				break;
			case '?':
				std::cerr << "give ?" << std::endl;
				exit(1);
		}
	}	

	unsigned long long size = 0;
	try
	{
		size = std::stoull(str_size);	
	} catch(...)
	{
		std::cerr << "incorrect_arg" << std::endl;
		exit(1);
	}

	myclone::BufOut test(outfile.c_str());
	std::ifstream in(infile);

	char *info = new char[size + 1];
	in.read(info, size);

	::time_t start = ::time(nullptr);
	test.write(info, size);
	::time_t end = ::time(nullptr);

	double t = end - start;
	unsigned long long mbyte = size >> 20;
	double speed = (mbyte * CLOCKS_PER_SEC) / t;

	std::cout << std::endl  
			  << "Time: " << t << " sec." << std::endl
			  << "Size: " << mbyte << std::endl
			  << "Speed: " << speed << " mb/sec. " << std::endl;
	delete[] info;

	return 0;
}

