#include <iostream>
#include <iomanip>
#include <vector>

#include <openssl/sha.h>

#include "../../mysql/include/util.h"

int main(int argc, char** argv)
{
	std::string str = "test-sha";
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHAUtil::sha256(str, hash);
	std::cout << "sha测试 input=" << str << std::endl;
	std::cout << "sha测试 output=";
	std::cout << std::setw(2) << std::setfill('0');
	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
	{
		std::cout << (uint32_t)hash[i] << " ";
	}
	std::cout << std::dec << std::endl;
	std::cout << std::dec << std::endl;
	return 0;
}