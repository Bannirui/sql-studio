#include <QApplication>
#include <iostream>

#include "mainwindow.h"
#include "tlogindialog.h"

#include "mysql/include/mysql_client.h"

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
	if (!client.connect_2_mysql_server())
	{
		std::cerr << "连接服务端失败\n";
		return -1;
	}
	return 0;
}
