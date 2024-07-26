//
// Created by dingrui on 2024/7/14.
//

#ifndef SQL_STUDIO__UTIL_H_
#define SQL_STUDIO__UTIL_H_

#include <vector>
#include <cstdint>

class ParserUtil
{
 public:
	/**
 	* 从byte数组中读取指定长度的数据
 	* <ul>
 	*   <li>uint8</li>
 	*   <li>uint16</li>
 	*   <li>uint32</li>
 	*   <li>uint64</li>
 	* </ul>
 	*/
	template<typename T>
	static T read_int_from_byte_arr(const std::vector<uint8_t>& buf, size_t& offset)
	{
		T val = *reinterpret_cast<const T*>(&buf[offset]);
		offset += sizeof(T);
		return val;
	}
	// 小端存储
	static uint32_t read_u24_from_byte_arr(const std::vector<uint8_t>& buf, size_t& offset);
	/**
	 * 从byte数组中读取以null结尾的字符串
	 */
	static std::string read_string_till_terminate(const std::vector<uint8_t>& buf, size_t& offset);
	/**
	 * 连续读n个byte
	 */
	static std::vector<uint8_t> read_n_bytes(const std::vector<uint8_t>& buf, size_t& offset, int n);
};
class SHAUtil
{
 public:
	/**
	 * 计算sha2散列值.
	 * @param hash str的sha2散列值
	 */
	static bool sha256(const std::string data, uint8_t* hash);
	/**
	 * caching_sha_password算法计算缓存密码.
	 */
	static std::string caching_sha2_pwd(const std::string& pwd, const std::string& salt);
};
#endif //SQL_STUDIO__UTIL_H_
