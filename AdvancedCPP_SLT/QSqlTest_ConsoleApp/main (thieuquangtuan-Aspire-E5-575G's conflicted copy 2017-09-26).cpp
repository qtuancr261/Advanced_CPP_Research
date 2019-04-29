#include <QCoreApplication>
#include <QtSql>
#include <iostream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout << "QtSQl" << std::endl;
    QSqlQueryModel* mModel{nullptr};
    // Connecting
    //QSqlDatabase miDataBase{QSqlDatabase::addDatabase("QODBC")};
    QSqlDatabase miDataBase{QSqlDatabase::addDatabase("QMYSQL")};
    //miDataBase.setDatabaseName("DRIVER={SQL SERVER}; SERVER=THIEUQUANGTUAN\\TQTSQLSERVER; DATABASE=SBSChap4SSMS; UID=sa; PWD=thematrix141; Trusted_Connection=Yes");
    //miDataBase.setDatabaseName("DRIVER={QMYSQL}; SERVER=Mysql@localhost:3306; DATABASE=QLDSD_D14; UID=root; PWD=thematrix141; Trusted_Connection=Yes");

    //miDataBase.setHostName("localhost");
    miDataBase.setUserName("root");
    miDataBase.setPassword("thematrix141");
    miDataBase.setDatabaseName("CUAHANG_BANGDIA");
    if (!miDataBase.open())
    {
        std::cout << "Of course ! It's impossible" << std::endl;
    }
    else
    {
        std::cout << "That's how I love Qt - Connect SQL Server successfully" << std::endl;
            mModel = new QSqlQueryModel();
            mModel->setQuery("select * from KHACHHANG");
            std::cout << " Row: " << mModel->rowCount() << std::endl;
            std::cout << " Column: " << mModel->columnCount() << std::endl;
    }
    delete mModel;
    return 0;
    return a.exec();
}
