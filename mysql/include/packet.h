//
// Created by dingrui on 2024/7/13.
//

#ifndef SQL_STUDIO__PACKET_H_
#define SQL_STUDIO__PACKET_H_

#include <vector>
#include <cstdint>

enum PacketType
{
	fail = -1, err, ok, biz
};
class Payload;
class MySQLPacket
{
 public:
	// int<3>	payload_length	Length of the payload. The number of bytes in the packet beyond the initial 4 bytes that make up the packet header.
	uint32_t payload_length;
	// int<1>	sequence_id	Sequence ID
	uint32_t sequence_id;
	// string<var>	payload	payload of the packet
	Payload* payload;
 public:
	MySQLPacket(Payload* payload);
 public:
	void print();
	void read(const std::vector<uint8_t>& buffer, std::function<void(void*)> const& fn);
	std::vector<uint8_t> write();
};

#endif //SQL_STUDIO__PACKET_H_
