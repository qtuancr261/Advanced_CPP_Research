#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;
bool createConnection(QString Driver, QString HostName, QString UserName, QString Password, QString DatabaseName)
{
    QSqlDatabase database{QSqlDatabase::addDatabase(Driver)};
    database.setHostName(HostName);
    database.setUserName(UserName);
    database.setPassword(Password);
    database.setDatabaseName(DatabaseName);
    if(!database.open())
    {
        cerr << "Database Error  >>>> ";
        return false;
    }
    cout << "Connecting successfully........................" << endl;
    return true;
}
bool executeQuery()
{
    QSqlQuery sqlStatement{};
    sqlStatement.exec("select * from NGANHANG ");
    while(sqlStatement.next())
    {
        QString productID{sqlStatement.value("id").toString()};
        QString productName{sqlStatement.value("password").toString()};
        cout << qPrintable(productID) << " : " << productName .toStdString()<< endl;
    }
    return true;
}

#endif // CONNECTION_H
