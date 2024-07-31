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
	static void write_u24_to_byte_arr(std::vector<uint8_t>& buf, size_t& offset, uint32_t val);
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
	static std::vector<uint8_t> scramble(std::vector<uint8_t> nonce, const std::string password);
};
#endif //SQL_STUDIO__UTIL_H_
