#include <iostream>
#include <vector>

#include "../../mysql/include/util.h"

int main(int argc, char** argv)
{
	std::vector<uint8_t> bytes;
	bytes.push_back('h');
	bytes.push_back('e');
	bytes.push_back('l');
	bytes.push_back('l');
	bytes.push_back('o');
	size_t i = 0;
	std::string str = ParserUtil::read_string_till_terminate(bytes, i);
	std::cout << str << std::endl;
	return 0;
}