//
// Created by dingrui on 2024/7/14.
//
#include <iostream>
#include <iomanip>
#include <sstream>
#include <memory>

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
void ParserUtil::write_u24_to_byte_arr(std::vector<uint8_t>& buf, size_t& offset, uint32_t val)
{
	for (int i = 0; i < 3; i++)
	{
		buf.at(offset++) = val & 0xff;
		val >>= 8;
	}
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
/**
 * scramble the password using the client's scheme.
 *
 * - mysql_native_password
 *   - message-digest: SHA1
 *   - inner message-digest-order: nonce + double_hashed_password
 * - caching_sha256_password
 *   - message-digest: SHA256
 *   - inner message-digest-order: double_hashed_password + nonce
 *
 * @param nonce nonce used between server and client
 * @param password cleartext password to be scrambled
 * @param digest_func digest function
 * @param nonce_before_double_hashed_password if true, nonce appears before
 * double_hashed_password; if false, nonce appears after double_hashed_password
 * @returns auth-response a client would send it
 */
std::vector<uint8_t> SHAUtil::scramble(std::vector<uint8_t> nonce, const std::string password)
{
	// in case of empty password, the hash is empty too
	if (password.empty()) return std::vector<uint8_t>{};
	const auto digest_size = EVP_MD_size(EVP_sha256());
	std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> digest_ctx(EVP_MD_CTX_new(), &EVP_MD_CTX_free);

	std::vector<uint8_t> hashed_password(digest_size);
	std::vector<uint8_t> double_hashed_password(digest_size);
	std::vector<uint8_t> hashed_nonce_and_double_hashed_password(digest_size);

	int ok{ 1 };
	ok &= EVP_DigestInit_ex(digest_ctx.get(), EVP_sha256(), nullptr);
	ok &= EVP_DigestUpdate(digest_ctx.get(), password.data(), password.size());
	ok &= EVP_DigestFinal_ex(digest_ctx.get(), hashed_password.data(), nullptr);

	ok &= EVP_DigestInit_ex(digest_ctx.get(), EVP_sha256(), nullptr);
	ok &= EVP_DigestUpdate(digest_ctx.get(), hashed_password.data(),
		hashed_password.size());
	ok &= EVP_DigestFinal_ex(digest_ctx.get(), double_hashed_password.data(),
		nullptr);

	ok &= EVP_DigestInit_ex(digest_ctx.get(), EVP_sha256(), nullptr);
	ok &= EVP_DigestUpdate(digest_ctx.get(), nonce.data(), nonce.size());
	ok &= EVP_DigestUpdate(digest_ctx.get(), double_hashed_password.data(), double_hashed_password.size());
	ok &= EVP_DigestFinal_ex(digest_ctx.get(), double_hashed_password.data(), nullptr);

	if (!ok) return std::vector<uint8_t>{};

	// scramble the hashed password with the nonce
	for (int i = 0; i < digest_size; ++i)
	{
		hashed_password[i] ^= double_hashed_password[i];
	}

	return hashed_password;
}
