//
// Created by dingrui on 2024/7/12.
//

#ifndef SQL_STUDIO__MYSQLCLIENT_H_
#define SQL_STUDIO__MYSQLCLIENT_H_

#include <string>
#include <vector>
#include <cstdint>

class MySQLPacket;
class MySQLClient
{
 private:
	std::string host;
	uint16_t port;
	std::string username;
	std::string pwd;

	int sock;

 public:
	MySQLClient(const std::string& host, uint16_t port, const std::string& username, const std::string& pwd);
	~MySQLClient();
 public:
	/**
	 * 建立tcp连接.
	 * @return -1标识连接失败
	 */
	int connect_to_server();
	bool receive_handshake_packet(MySQLPacket& packet);
	bool send_handshake_response();

 private:
	std::vector<uint8_t> create_handshake_response();
};

#endif //SQL_STUDIO__MYSQLCLIENT_H_
