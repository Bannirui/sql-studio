//
// Created by dingrui on 2024/7/13.
//

#include "packet.h"
#include "util.h"
#include "payload.h"

#include <cstring>
#include <iostream>

MySQLPacket::MySQLPacket(Payload* payload)
	: payload(payload)
{
}

void MySQLPacket::parse(const std::vector<uint8_t>& buffer)
{
	size_t i = 0;
	this->payload_length = ParserUtil::read_u24_from_byte_arr(buffer, i);
	this->sequence_id = ParserUtil::read_int_from_byte_arr<uint8_t>(buffer, i);
	this->payload->parse(buffer);
}

void MySQLPacket::print()
{
	std::cout << "payload len: " << static_cast<int>(this->payload_length) << "\n";
	std::cout << "sequence id: " << static_cast<int>(this->sequence_id) << "\n";
	this->payload->print();
}