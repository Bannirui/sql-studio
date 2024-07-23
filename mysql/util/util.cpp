//
// Created by dingrui on 2024/7/14.
//
#include <iostream>
#include <sstream>
#include <iomanip>

#include <openssl/sha.h>
#include <openssl/hmac.h>

#include "../include/util.h"

uint32_t ParserUtil::read_u24_from_byte_arr(const std::vector<uint8_t>& buf, size_t& offset)
{
	uint32_t val = buf[offset] | (buf[offset + 1] << 8) | (buf[offset + 2] << 16);
	offset += 3;
	return val;
}
std::string ParserUtil::read_string_till_terminate(const std::vector<uint8_t>& buf, size_t& offset)
{
	std::string str;
	while (buf[offset] != '\0')
	{
		str.push_back(buf[offset]);
		++offset;
	}
	// 跳过null终止符
	++offset;
	return str;
}
std::vector<uint8_t> ParserUtil::read_n_bytes(const std::vector<uint8_t>& buf, size_t& offset, int n)
{
	std::vector<uint8_t> bytes(buf.begin() + offset, buf.begin() + offset + n);
	offset += n;
	return bytes;
}
std::string SHAUtil::sha256(const std::string& str)
{
	return {};
	// TODO: 2024/7/23
//	unsigned char hash[SHA256_DIGEST_LENGTH];
//	SHA256_CTX sha256;
//	SHA256_Init(&sha256);
//	SHA256_Update(&sha256, str.c_str(), str.size());
//	SHA256_Final(hash, &sha256);
//
//	std::stringstream ss;
//	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
//	{
//		ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
//	}
//	return ss.str();
}