//
// Created by dingrui on 2024/7/13.
//

#ifndef SQL_STUDIO__PACKET_H_
#define SQL_STUDIO__PACKET_H_

#include <vector>
#include <cstdint>

class HandshakeV10Packet
{
 public:
	uint32_t payload_length;
	uint32_t sequence_id;

	u_int8_t protocol_version;
	std::string server_version;
	uint32_t connection_id;

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

#endif //SQL_STUDIO__PACKET_H_
