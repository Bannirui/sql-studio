//
// Created by dingrui on 2024/7/12.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

#include "mysqlclient.h"
#include "packet.h"

#define ARR_LEN 1024

MySQLClient::MySQLClient(const std::string& host, uint16_t port, const std::string& username, const std::string& pwd)
	: host(host), port(port), username(username), pwd(pwd), sock(0)
{
}

MySQLClient::~MySQLClient()
{
	if (this->sock > 0)
	{
		std::cout << "close the tcp connect, fd=" << this->sock << "\n";
		close(this->sock);
	}
}

int MySQLClient::connect_to_server()
{
	if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
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
	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cerr << "connect failed\n";
		return false;
	}
	std::cout << "connect to mysql server\n";
	return true;
}

bool MySQLClient::receive_handshake_packet(MySQLPacket& packet)
{
	std::vector<uint8_t> buf(ARR_LEN);
	ssize_t bytes_received = recv(this->sock, buf.data(), buf.size(), 0);
	if (bytes_received < 0)
	{
		std::cerr << "fail to receive handshake packet\n";
		return false;
	}
	buf.resize(bytes_received);
#if(DEBUG)
	// 握手包的原始数据
	std::cout << "raw handshake packet data:\n";
	for (const auto& byte : buf)
	{
		std::cout << std::hex << static_cast<int>(byte) << " ";
	}
	std::cout << std::dec << std::endl;
#endif
	// 解析握手包
	packet.parse(buf);
	return true;
}
