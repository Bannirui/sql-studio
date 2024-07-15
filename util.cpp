//
// Created by dingrui on 2024/7/14.
//
#include "util.h"

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
