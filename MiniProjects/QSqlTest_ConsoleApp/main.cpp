#include <QCoreApplication>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include "connection.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout << "QtSQl" << std::endl;
    // Connecting
    QSqlDatabase miDataBase{QSqlDatabase::addDatabase("QODBC")};
    miDataBase.setConnectOptions();
    //QSqlDatabase miDataBase2{QSqlDatabase::addDatabase("QMYSQL")};
    miDataBase.setDatabaseName("DRIVER={SQL SERVER}; SERVER=THIEUQUANGTUAN\\TQTSQLSERVER; DATABASE=MyDB; UID=sa; PWD=thematrix141; Trusted_Connection=Yes");
    if (!miDataBase.open())
    {
        cerr << "Cannot connect" << endl;
    }
    //miDataBase.setDatabaseName("DRIVER={QMYSQL}; SERVER=localhost; DATABASE=QLDSD_D14; UID=root; PWD=thematrix141; Trusted_Connection=Yes");

    //miDataBase2.setHostName("localhost");
    //miDataBase2.setUserName("root");
    //miDataBase2.setPassword("thematrix141");
    //miDataBase2.setDatabaseName("CUAHANG_BANGDIA");
    /*if(createConnection("QMYSQL", "localhost", "root", "thematrix141", "network"))
    {
        executeQuery();
    }*/
    return 0;
    return a.exec();
}
