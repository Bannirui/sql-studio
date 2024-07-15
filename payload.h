//
// Created by dingrui on 2024/7/14.
//

#ifndef SQL_STUDIO__PAYLOAD_H_
#define SQL_STUDIO__PAYLOAD_H_

#include <vector>
#include <cstdint>

class Payload
{
 protected:
	virtual void parse(const std::vector<uint8_t>& buffer) = 0;
	virtual void print() = 0;
};
class HandshakePayload : public Payload
{
 public:
	u_int8_t protocol_version;
	std::string server_version;
	uint32_t connection_id;
};
class HandshakeV9Payload : public HandshakePayload
{
 public:
	std::string scramble;
 public:
	void parse(const std::vector<uint8_t>& buffer);
	void print();
};
class HandshakeV10Payload : public HandshakePayload
{
 public:
	std::vector<uint8_t> auth_plugin_data_part1;
	uint8_t filler;
	uint16_t capability_flags_1;
	uint8_t character_set;
	uint16_t status_flags;
	uint16_t capability_flags_2;
	uint8_t auth_plugin_data_len;
	std::vector<uint8_t> reserved;
	std::vector<uint8_t> auth_plugin_data_part_2;
	std::string auth_plugin_name;
 public:
	void parse(const std::vector<uint8_t>& buffer);
	void print();
};

#endif //SQL_STUDIO__PAYLOAD_H_
