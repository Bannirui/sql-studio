//
// Created by dingrui on 2024/7/12.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <functional>
#include <iomanip>

#include "include/mysql_client.h"
#include "include/packet.h"
#include "include/mysql_macros.h"
#include "include/payload.h"
#include "util.h"

MySQLClient::MySQLClient(const std::string& host,
	uint16_t port,
	const std::string& username,
	const std::string& pwd,
	const std::string& db_name)
	: host(host), port(port), username(username), pwd(pwd), db_name(db_name), sock_fd(-1)
{
}

MySQLClient::~MySQLClient()
{
	if (this->sock_fd > 0)
	{
		std::cout << "MySQLClient析构tcp的连接 fd=" << this->sock_fd << "\n";
		close(this->sock_fd);
	}
}
bool MySQLClient::connect_2_mysql_server()
{
	if (this->sock_fd < 0)
	{
		if (!this->init_tcp())
		{
			std::cerr << "tcp初始化失败\n";
			return false;
		}
	}
	this->handshake();
	return true;
}
int MySQLClient::init_tcp()
{
	if ((this->sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		std::cerr << "socket create err\n";
		return false;
	}
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(this->port);
	if (inet_pton(AF_INET, this->host.c_str(), &serv_addr.sin_addr) <= 0)
	{
		std::cerr << "invalid addr, not supported\n";
		return false;
	}
	if (connect(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cerr << "tcp连接服务器失败\n";
		return false;
	}
	std::cout << "tcp连接服务器成功\n";
	return true;
}
void MySQLClient::handshake()
{
	std::vector<uint8_t> packet = this->receive_packet();
	if (packet.empty()) return;
	std::cout << "客户端收到服务端的初始握手包 ";
	this->print_packet(packet);
	this->process_packet(packet);
}
std::vector<uint8_t> MySQLClient::receive_packet()
{
	std::vector<uint8_t> buf(ARR_LEN);
	ssize_t len = recv(this->sock_fd, buf.data(), buf.size(), 0);
	if (len <= 0)
	{
		std::cerr << "接收服务端数据失败\n";
		len = 0;
	}
	buf.resize(len);
	return buf;
}
void MySQLClient::print_packet(const std::vector<uint8_t>& packet)
{
	std::cout << std::hex;
	for (uint8_t ch : packet)
		std::cout << std::setw(2) << std::setfill('0') << static_cast<uint32_t>(ch) << " ";
	std::cout << std::dec << std::endl;
}
void MySQLClient::process_packet(const std::vector<uint8_t>& packet)
{
	// int<3>	payload_length
	// int<1>	sequence_id
	if (packet.size() < 4)
	{
		std::cerr << "协议包格式不正确\n";
		return;
	}
	// 根据第5个byte判断协议包类型
	uint8_t packet_type = packet[4];
	switch (packet_type)
	{
	case OK_PACKET_1:
	case OK_PACKET_2:
		this->process_ok_packet(packet);
		break;
	case ERR_PACKET:
		this->process_error_packet(packet);
		break;
	case HANDSHAKE_V9:
		this->process_handshake_v9_packet(packet);
		break;
	case HANDSHAKE_V10:
		this->process_handshake_v10_packet(packet);
		break;
	default:
		std::cout << "协议包的类型是0x" << std::hex << std::setw(2) << std::setfill('0')
				  << static_cast<uint32_t >(packet_type) << " 暂不支持" << std::endl;
		std::cout << std::dec;
		break;
	}
}
void MySQLClient::process_ok_packet(const std::vector<uint8_t>& packet)
{
	// TODO: 2024/7/21
}
void MySQLClient::process_error_packet(const std::vector<uint8_t>& packet)
{
	std::cerr << "收到error包\n";
	size_t i = 0;
	uint32_t len = ParserUtil::read_u24_from_byte_arr(packet, i);
	uint8_t seq_id = ParserUtil::read_int_from_byte_arr<u_int8_t>(packet, i);
	uint8_t header = ParserUtil::read_int_from_byte_arr<uint8_t>(packet, i);
	uint16_t err_code = ParserUtil::read_int_from_byte_arr<uint16_t>(packet, i);
	std::vector<uint8_t> sql_state_marker = ParserUtil::read_n_bytes(packet, i, 1);
	std::vector<uint8_t> sql_state = ParserUtil::read_n_bytes(packet, i, 5);
	std::cout << "header=0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<uint32_t>(header)
			  << std::endl;
	std::cout << "err_code=0x" << std::hex << std::setw(4) << std::setfill('0') << static_cast<uint32_t>(err_code)
			  << std::endl;
	std::cout << std::dec;
	std::cout << "sql_state_marker: ";
	for (auto ch : sql_state_marker) std::cout << ch << " ";
	std::cout << std::endl;
	std::cout << "sql_state: ";
	for (auto ch : sql_state) std::cout << ch << " ";
	std::cout << std::endl;
}
void MySQLClient::process_handshake_v9_packet(const std::vector<uint8_t>& packet)
{
// TODO: 2024/7/21
}
void MySQLClient::process_handshake_v10_packet(const std::vector<uint8_t>& packet)
{
	HandshakeV10Payload payload;
	MySQLPacket m_packet(&payload);
	m_packet.read(packet);
	m_packet.print();
	auto* handshake_v10_payload = (HandshakeV10Payload*)(m_packet.payload);
	uint32_t server_capabilities =
		(handshake_v10_payload->capability_flags_2 << 16) | handshake_v10_payload->capability_flags_1;
	std::cout << "capabilities=0x" << std::hex << static_cast<uint32_t >(server_capabilities);
	this->server_capabilities = server_capabilities;
	if (server_capabilities & CLIENT_PROTOCOL_41)
	{
		HandshakeResponse41
			handshake_response_payload(this->username, this->pwd, this->db_name, server_capabilities);
		handshake_response_payload.client_flag = CLIENT_PROTOCOL_41 | CLIENT_PLUGIN_AUTH;
		handshake_response_payload.max_packet_size = 0xffffffff;
		handshake_response_payload.character_set = 0x21;
		for (int i = 0; i < 23; i++)
		{
			handshake_response_payload.filler.push_back(0x00);
		}
		handshake_response_payload.username = this->username;
		if (server_capabilities & CLIENT_PLUGIN_AUTH_LENENC_CLIENT_DATA)
		{
			// string<length>	auth_response	opaque authentication response data generated by Authentication Method indicated by the plugin name field.
			// TODO: 2024/7/20
		}
		else
		{
			// int<1>	auth_response_length	length of auth_response
			// string<length>	auth_response	opaque authentication response data generated by Authentication Method indicated by the plugin name field.
		}
		if (server_capabilities & CLIENT_CONNECT_WITH_DB)
		{
			// string<NUL>	database	initial database for the connection. This string should be interpreted using the character set indicated by character set field.
			// 数据库名
			handshake_response_payload.database = this->db_name;
		}
		// int<1>	zstd_compression_level	compression level for zstd compression algorithm
		MySQLPacket handshake_resp_packet(&handshake_response_payload);
		std::vector<uint8_t> packet_bytes = handshake_resp_packet.write();
		this->send_packet(packet_bytes);
	}
	else
	{
		// TODO: 2024/7/21
	}
	std::vector<uint8_t> auth_resp_byte = this->receive_packet();
	this->process_packet(auth_resp_byte);
}
bool MySQLClient::send_packet(std::vector<uint8_t>& packet)
{
	// send系统函数的第4个参数flags
	// #define MSG_OOB        0x1  /* process out-of-band data */
	// #define MSG_DONTROUTE  0x4  /* bypass routing, use direct interface */
	if (send(this->sock_fd, packet.data(), packet.size(), 0) < 0)
	{
		std::cerr << "客户端发送数据包失败\n";
		return false;
	}
	std::cout << "客户端发送数据包成功\n";
	return true;
}