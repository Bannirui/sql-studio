//
// Created by dingrui on 2024/7/12.
//

#ifndef SQL_STUDIO__MYSQL_CLIENT_H_
#define SQL_STUDIO__MYSQL_CLIENT_H_

#include <string>
#include <vector>
#include <cstdint>
#include "packet.h"

#define ARR_LEN 0x01<<10

#define OK_PACKET_1 0x00
#define OK_PACKET_2 0xfe
#define ERR_PACKET 0xff
#define HANDSHAKE_V9 0x09
#define HANDSHAKE_V10 0x0a

class MySQLPacket;
class MySQLClient
{
 public:
	/**
	 * @param host 域名
	 * @param port 端口
	 * @param username 用户名
	 * @param pwd 密码
	 * @param db_name 数据库
	 */
	MySQLClient(const std::string& host,
		uint16_t port,
		const std::string& username,
		const std::string& pwd,
		const std::string& db_name);
	~MySQLClient();
	/**
	 * 登陆.
	 */
	bool connect_2_mysql_server();
	void query();
 private:
	/**
	 * 初始化tcp连接.
	 * @return socket fd
	 */
	int init_tcp();
	void handshake();
	std::vector<uint8_t> receive_packet();
	void print_packet(const std::vector<uint8_t>& packet);
	void process_packet(const std::vector<uint8_t>& packet);
	void process_ok_packet(const std::vector<uint8_t>& packet);
	void process_error_packet(const std::vector<uint8_t>& packet);
	void process_handshake_v9_packet(const std::vector<uint8_t>& packet);
	void process_handshake_v10_packet(const std::vector<uint8_t>& packet);
	bool send_packet(std::vector<uint8_t>& packet);
 private:
	std::string host;
	uint16_t port;
	std::string username;
	std::string pwd;
	std::string db_name;
	int sock_fd;
	uint32_t server_capabilities;
};

#endif //SQL_STUDIO__MYSQL_CLIENT_H_
