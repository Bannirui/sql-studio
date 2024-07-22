//
// Created by dingrui on 2024/7/14.
//

#ifndef SQL_STUDIO__PAYLOAD_H_
#define SQL_STUDIO__PAYLOAD_H_

#include <vector>
#include <cstdint>

class Payload
{
 public:
	virtual void print();
	virtual void read(const std::vector<uint8_t>& buffer);
	virtual std::vector<uint8_t> write();
};
// 客户端接收服务端
class InPayload : public Payload
{
	// 字节数组反序列化
	void read(const std::vector<uint8_t>& buffer) override = 0;
};
// 客户端向服务端发送
class OutPayload : public Payload
{
	// 序列化成字节数组
	std::vector<uint8_t> write() override = 0;
};
class HandshakePayload : public InPayload
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
	void print() override;
	void read(const std::vector<uint8_t>& buffer) override;
};
class HandshakeV10Payload : public HandshakePayload
{
 public:
	std::vector<uint8_t> auth_plugin_data_part1;
	uint8_t filler;
	// The lower 2 bytes of the Capabilities Flags
	uint16_t capability_flags_1;
	uint8_t character_set;
	uint16_t status_flags;
	// The upper 2 bytes of the Capabilities Flags
	uint16_t capability_flags_2;
	uint8_t auth_plugin_data_len;
	std::vector<uint8_t> reserved;
	std::vector<uint8_t> auth_plugin_data_part_2;
	std::string auth_plugin_name;
 public:
	void print() override;
	void read(const std::vector<uint8_t>& buffer) override;
};
class AuthResponse : public OutPayload
{
 public:
	virtual std::vector<uint8_t> generate_auth_response(const std::string& password,
		const std::vector<unsigned char>& nonce) = 0;
};
class HandshakeResponse320 : public AuthResponse
{
 public:
	// int<2>	client_flag	Capabilities Flags, only the lower 16 bits. CLIENT_PROTOCOL_41 should never be set
	uint16_t client_flag;
	//int<3>	max_packet_size	maximum packet size, 0xFFFFFF max
	uint32_t max_packet_size;
	// string<NUL>	username	login user name
	std::string username;
	// string<NUL>	auth-response	Opaque authentication response data generated by Authentication Method indicated by the plugin name field.
	// string<EOF>	auth-response	Opaque authentication response data generated by Authentication Method indicated by the plugin name field.
	std::string auth_response;
	// string<NUL>	database	initial database for the connection. This string should be interpreted using the character set indicated by character set field.
	std::string database;
 public:
	void print() override;
	std::vector<uint8_t> write() override;
	std::vector<uint8_t> generate_auth_response(const std::string& password,
		const std::vector<unsigned char>& nonce) override;
};
class HandshakeResponse41 : public AuthResponse
{
 private:
	std::string pwd;
	uint32_t server_capabilities;
 public:
	// int<4> client_flag Capabilities Flags, CLIENT_PROTOCOL_41 always set.
	uint32_t client_flag;
	// int<4> max_packet_size maximum packet size
	uint32_t max_packet_size;
	// int<1> character_set client charset a_protocol_character_set, only the lower 8-bits
	// 0x08	latin1_swedish_ci
	// 0x21	utf8mb3_general_ci
	// 0x3f	binary
	uint8_t character_set;
	// string[23] filler filler to the size of the handhshake response packet. All 0s.
	std::string filler;
	// string<NUL> username login user name
	std::string username;
	// string<length> auth_response    opaque authentication response data generated by Authentication Method indicated by the plugin name field.
	// int<1> auth_response_length length of auth_response
	// string<length> auth_response opaque authentication response data generated by Authentication Method indicated by the plugin name field.
	uint8_t auth_response_length;
	std::string auth_response;
	// string<NUL> database    initial database for the connection. This string should be interpreted using the character set indicated by character set field.
	std::string database;
	// string<NUL> client_plugin_name    the Authentication Method used by the client to generate auth-response value in this packet. This is an UTF-8 string.
	std::string client_plugin_name;
	// int<lenenc> length of all key-values    affected rows
	// string<lenenc>    key1    Name of the 1st client attribute
	// string<lenenc>    value1    Value of the 1st client attribute

	// int<1> zstd_compression_level compression level for zstd compression algorithm
	uint8_t zstd_compression_level;
 public:
	HandshakeResponse41(const std::string& username,
		const std::string& pwd,
		const std::string& db_name,
		uint32_t server_capabilities);
 public:
	void print() override;
	std::vector<uint8_t> write() override;
	std::vector<uint8_t> generate_auth_response(const std::string& password,
		const std::vector<unsigned char>& nonce) override;
};
class OkPayload : public InPayload
{
 public:
	// int<1>	header	0x00 or 0xFE the OK packet header
	uint8_t header;
	// int<lenenc>	affected_rows	affected rows
	// int<lenenc>	last_insert_id	last insert-id
	// int<2>	status_flags	SERVER_STATUS_flags_enum
	// int<2>	warnings	number of warnings
	// string<lenenc>	info	human readable status information
	// string<lenenc>	session state info	Session State Information
 public:
	void print() override;
	void read(const std::vector<uint8_t>& buffer) override;
};
class ErrPayload : public InPayload
{
 public:
	// int<1>	header	0xFF ERR packet header
	uint8_t header;
	// int<2>	error_code	error-code
	uint16_t err_code;
	// string[1]	sql_state_marker	# marker of the SQL state
	std::string sql_state_marker;
	// string[5]	sql_state	SQL state
	std::string sql_state;
	// string<EOF>	error_message	human readable error message
	std::string error_message;
 public:
	void print() override;
	void read(const std::vector<uint8_t>& buffer) override;
};
#endif //SQL_STUDIO__PAYLOAD_H_
