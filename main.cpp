#include <QApplication>
#include <iostream>

#include "mainwindow.h"
#include "tlogindialog.h"

#include "MySQLClient.h"
#include "packet.h"

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

	MySQLClient client("127.0.0.1", 3306, "root", "19920308");
	if (!client.connect_to_server())
	{
		return -1;
	}
	HandshakeV10Packet handshake_packet;
	if (!client.receive_handshake_packet(handshake_packet))
	{
		return -1;
	}
	handshake_packet.print();
	return 0;
}
