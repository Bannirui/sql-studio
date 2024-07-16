//
// Created by dingrui on 2024/7/13.
//

#ifndef SQL_STUDIO__PACKET_H_
#define SQL_STUDIO__PACKET_H_

#include <vector>
#include <cstdint>

class Payload;
class MySQLPacket
{
 public:
	uint32_t payload_length;
	uint32_t sequence_id;
	Payload* payload;
 public:
	MySQLPacket(Payload* payload);
 public:
	void parse(const std::vector<uint8_t>& buffer);
	void print();
};

#endif //SQL_STUDIO__PACKET_H_
