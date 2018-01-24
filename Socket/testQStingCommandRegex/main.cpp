#include <QCoreApplication>
#include <QString>
#include <iostream>
#include <QtDebug>
int main(int argc, char *argv[])
{
    char cString[]{"tuan send: <FILE> testFile.odt 125"};
    QString cmd(cString);
    for (QString subCmd : cmd.split(" "))
        qDebug() << subCmd;
    qDebug() << cmd.section(" ", -1, -1);
    if (cmd.section(" ", 2, 2) == QString("<FILE>"))
        qDebug() << "perfect";
    char cString2[]{"\n"};
    std::printf("-- %s ", cString2);

}
