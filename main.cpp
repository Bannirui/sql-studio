#include <QApplication>
#include <iostream>

#include "mainwindow.h"
#include "tlogindialog.h"

#include "mysql/include/mysql_client.h"
#include "mysql/include/packet.h"
#include "mysql/include/payload.h"

int main(int argc, char* argv[])
{
//	QApplication a(argc, argv);
//	TLoginDialog* login = new TLoginDialog();
//	if (login->exec() == QDialog::Accepted)
//	{
//		MainWindow w;
//		return a.exec();
//	}
//	else
//	{
//		return 0;
//	}

	MySQLClient client("127.0.0.1", 3306, "root", "19920308", "test");
	if (!client.connect_to_server())
	{
		std::cerr << "连接服务端失败\n";
		return -1;
	}
	HandshakeV10Payload handshake_v10_payload;
	MySQLPacket handshake_packet(&handshake_v10_payload);
	if (client.recv_packet(handshake_packet, [&client](void* v) -> void
	{ client.server_capabilities = *(uint32_t*)v; })==PacketType::fail)
	{
		std::cerr << "接收服务端初始握手包失败\n";
		return -1;
	}
	std::cout << "接收服务端初始握手包成功\n";
#ifdef TEST_DEBUG
	handshake_packet.print();
#endif
	if (!client.send_handshake_response())
	{
		std::cerr << "客户端回复握手包失败\n";
		return -1;
	}
	std::cout << "客户端回复握手包成功\n";
	return 0;
}
