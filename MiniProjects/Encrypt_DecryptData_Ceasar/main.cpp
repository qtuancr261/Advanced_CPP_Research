#include <QCoreApplication>
#include <QBuffer>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include "ceasarcipherdevice.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // read file data into a byte array
    QFile buffer{"GT.txt"};
    buffer.open(QIODevice::ReadOnly);
    QByteArray text{buffer.readAll()};
    buffer.close();

    // encryption
    buffer.open(QIODevice::WriteOnly);
    CeasarCipherDevice encryptDevice;
    encryptDevice.setKey(3);
    encryptDevice.setRootDevice(&buffer);
    encryptDevice.open(buffer.openMode());
    encryptDevice.write(text);
    qDebug() << text;
    buffer.close();
    encryptDevice.close();

    // decryption
    buffer.open(QIODevice::ReadOnly);
    CeasarCipherDevice decryptDevice;
    decryptDevice.setKey(3);
    decryptDevice.setRootDevice(&buffer);
    //buffer.open(QIODevice::ReadOnly);
    decryptDevice.open(buffer.openMode());
    qDebug() << decryptDevice.readAll();
    buffer.close();
    decryptDevice.close();

    buffer.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream{&buffer};
    stream << "Today is " << QDate::currentDate().toString() << endl;

    QTextStream qout{stdout};
    qout << "Welcome to qiostream :v" << endl;
    return 0;
    return a.exec();
}
