//
// Created by dingrui on 2024/7/14.
//
#include <iostream>
#include <iomanip>
#include <sstream>

#include <openssl/evp.h>
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

bool SHAUtil::sha256(const std::string data, uint8_t* hash)
{
	EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
	if (!mdctx)
	{
		std::cerr << "EVP_MD_CTX_new() failed\n";
		return false;
	}
	if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1)
	{
		std::cerr << "EVP_DigestInit_ex() failed\n";
		EVP_MD_CTX_free(mdctx);
		return false;
	}
	if (EVP_DigestUpdate(mdctx, data.c_str(), data.size()) != 1)
	{
		std::cerr << "EVP_DigestUpdate() failed\n";
		EVP_MD_CTX_free(mdctx);
		return false;
	}
	unsigned int hash_len;
	if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1)
	{
		std::cerr << "EVP_DigestFinal_ex() failed\n";
		EVP_MD_CTX_free(mdctx);
		return false;
	}
	EVP_MD_CTX_free(mdctx);
	return true;
}
std::string SHAUtil::caching_sha2_pwd(const std::string& pwd, const std::string& salt)
{
	return {};
//	unsigned char hash[SHA256_DIGEST_LENGTH];
//	sha256(salt, hash);
//	unsigned char* hmac = HMAC(EVP_sha256(), pwd.c_str(), pwd.size(), hash, SHA256_DIGEST_LENGTH, NULL, NULL);
//	std::stringstream ss;
//	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
//	{
//		ss << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)hmac[i];
//	}
//	return ss.str();
}