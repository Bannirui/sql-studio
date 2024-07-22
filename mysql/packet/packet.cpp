//
// Created by dingrui on 2024/7/13.
//

#include <iostream>

#include "../include/packet.h"
#include "../include/util.h"
#include "../include/payload.h"

MySQLPacket::MySQLPacket(Payload* payload)
	: payload(payload)
{
}
void MySQLPacket::print()
{
	std::cout << "payload len: " << static_cast<int>(this->payload_length) << "\n";
	std::cout << "sequence id: " << static_cast<int>(this->sequence_id) << "\n";
	this->payload->print();
}
void MySQLPacket::read(const std::vector<uint8_t>& buffer)
{
	size_t i = 0;
	this->payload_length = ParserUtil::read_u24_from_byte_arr(buffer, i);
	this->sequence_id = ParserUtil::read_int_from_byte_arr<uint8_t>(buffer, i);
	this->payload->read(buffer);
}
std::vector<uint8_t> MySQLPacket::write()
{
	std::vector<uint8_t> packet;
	for (int i = 0; i < 3; i++)
	{
		packet.push_back((this->payload_length >> (i * 8)) & 0xff);
	}
	packet.push_back(this->sequence_id & 0xff);
	std::vector<uint8_t> payload_bytes = this->payload->write();
	packet.insert(packet.end(), payload_bytes.begin(), payload_bytes.end());
	return packet;
}