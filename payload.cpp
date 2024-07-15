//
// Created by dingrui on 2024/7/14.
//

#include "payload.h"
#include "util.h"

#include <iostream>

#define    CLIENT_PLUGIN_AUTH   (1UL << 19)

void HandshakeV10Payload::parse(const std::vector<uint8_t>& buffer)
{
	size_t i = 4;
	this->protocol_version = ParserUtil::read_int_from_byte_arr<uint8_t>(buffer, i);
	this->server_version = ParserUtil::read_string_till_terminate(buffer, i);
	this->connection_id = ParserUtil::read_int_from_byte_arr<uint32_t>(buffer, i);
	this->auth_plugin_data_part1 = ParserUtil::read_n_bytes(buffer, i, 8);
	this->filler = ParserUtil::read_int_from_byte_arr<uint8_t>(buffer, i);
	this->capability_flags_1 = ParserUtil::read_int_from_byte_arr<uint16_t>(buffer, i);
	this->character_set = ParserUtil::read_int_from_byte_arr<uint8_t>(buffer, i);
	this->status_flags = ParserUtil::read_int_from_byte_arr<uint16_t>(buffer, i);
	this->capability_flags_2 = ParserUtil::read_int_from_byte_arr<uint16_t>(buffer, i);
	int capability_flags = (this->capability_flags_2 << 16) | this->capability_flags_1;
	if (capability_flags & CLIENT_PLUGIN_AUTH)
		this->auth_plugin_data_len = ParserUtil::read_int_from_byte_arr<uint8_t>(buffer, i);
	else this->auth_plugin_data_len = 0;
	this->reserved = ParserUtil::read_n_bytes(buffer, i, 10);
	this->auth_plugin_data_part_2 =
		ParserUtil::read_n_bytes(buffer, i, std::max(13, static_cast<int>(this->auth_plugin_data_len) - 8));
	if (capability_flags & CLIENT_PLUGIN_AUTH)
	{
		this->auth_plugin_name = ParserUtil::read_string_till_terminate(buffer, i);
	}
}
void HandshakeV10Payload::print()
{
	std::cout << "protocol version: " << static_cast<int>(this->protocol_version) << "\n";
	std::cout << "server version: " << this->server_version << "\n";
	std::cout << "connection id: " << this->connection_id << "\n";
	std::cout << "filler: " << this->filler << "\n";
	std::cout << "capability_flags_1: " << this->capability_flags_1 << "\n";
	std::cout << "character_set: " << this->character_set << "\n";
	std::cout << "status_flags: " << this->status_flags << "\n";
	std::cout << "capability_flags_2: " << this->capability_flags_2 << "\n";
	std::cout << "auth_plugin_data_len: " << this->auth_plugin_data_len << "\n";
	std::cout << "auth_plugin_name: " << this->auth_plugin_name << "\n";
}