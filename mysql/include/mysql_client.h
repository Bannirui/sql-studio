//
// Created by dingrui on 2024/7/12.
//

#ifndef SQL_STUDIO__MYSQL_CLIENT_H_
#define SQL_STUDIO__MYSQL_CLIENT_H_

#include <string>
#include <vector>
#include <cstdint>
#include "packet.h"

class MySQLPacket;
class MySQLClient
{
 public:
	std::string host;
	uint16_t port;
	std::string username;
	std::string pwd;

	std::string db_name;

	int sock;
	/**
	 * 服务端capabilities.
	 * 服务端向客户端发送初始握手包的时候会发送过来
	 */
	uint32_t server_capabilities;

 public:
	MySQLClient(const std::string& host, uint16_t port, const std::string& username, const std::string& pwd, const std::string& db_name);
	~MySQLClient();
 public:
	/**
	 * 建立tcp连接.
	 * @return -1标识连接失败
	 */
	int connect_to_server();
	/**
	 * 客户端接收服务端字节数据 解析成数据包.
	 * <ul>
	 *   <li>tcp连接建立之后 服务端会向客户端发送初始握手包</li>
	 * </ul>
	 * @param packet 要解析成的数据包
	 * @param fn 回调函数 比如需要获取初始握手包中的server_capabilities
	 */
	int recv_packet(MySQLPacket& packet, std::function<void (void*)>const &fn);
	/**
	 * 客户端收到服务端初始握手包之后回复握手包.
	 */
	bool send_handshake_response();
 private:
	bool send_packet(MySQLPacket& packet);
};

#endif //SQL_STUDIO__MYSQL_CLIENT_H_
