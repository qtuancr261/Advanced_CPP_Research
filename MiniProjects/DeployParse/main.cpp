#include <QCoreApplication>
#include <QFile>
#include <QMap>
#include <QRegularExpression>
#include <QTextStream>
#include <QtDebug>
#include <iostream>
struct DBInfo {
	// QString name;
	QStringList address;
	QString kvNote;

	DBInfo() = default;
	~DBInfo() = default;
};
// data
// S1 - 127.0.0.1
QMap<QString, QString> serverMap;
// if - info
QMap<QString, DBInfo> dbMap;
// regex
QRegularExpression regexIP{"^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$"};
QRegularExpression regexSvIndex{"^S[0-9]{1,2}"};
int main(int argc, char *argv[]) {
	// QCoreApplication a(argc, argv);
	for (int i{}; i < argc; ++i) std::cout << argv[i] << std::endl;
	QFile deployNote{argv[1]};
	if (deployNote.open(QFile::ReadOnly)) {
		QTextStream readStream{&deployNote};
		QString line{""};
		while (readStream.readLineInto(&line)) {
			// qDebug() << line;
			line = line.simplified();
			QStringList paths = line.split('|');
			// skip this line
			if (paths.size() <= 1 || paths[0].trimmed() == "Name" || paths[0].trimmed() == "Index") continue;
			// qDebug() << line.simplified();
			for (int i{}; i < paths.size(); ++i) {
				// Parse Server - IP
				QRegularExpressionMatch matchIP = regexIP.match(paths[i].trimmed());
				if (matchIP.hasMatch()) {
					// qDebug() << paths[i - 1] << "-> " << paths[i];
					serverMap.insert(paths[i - 1].trimmed(), paths[i].trimmed());
					break;
				}
				// key-value note
				if (dbMap.contains(paths[0].trimmed())) {
					dbMap[paths[0].trimmed()].kvNote = paths[1].trimmed();
					// qDebug() << paths[0].trimmed() << ": " << dbMap[paths[0].trimmed()].kvNote;
					break;
				}
				// host port note
				QRegularExpressionMatch matchSVIndex = regexSvIndex.match(paths[0].trimmed());
				if (!matchSVIndex.hasMatch()) {
					// qDebug() << paths[0].trimmed();
					dbMap.insert(paths[0].trimmed(), DBInfo());
					//
					for (int j = 1; j < paths.size(); ++j) {
						if (j >= 5) break;
						dbMap[paths[0].trimmed()].address.append(paths.at(j).trimmed());

						// qDebug() << paths[i].trimmed();
					}
					break;
				}
			}
		}
		deployNote.close();
	}
	auto iter = dbMap.begin();
	for (; iter != dbMap.end(); ++iter) {
		QStringList hostport{iter.value().address};
		if (hostport.size() > 3 && !hostport.at(3).isEmpty()) {
			QString host{serverMap[hostport.at(3)]};
			if (host.isEmpty()) {
				for (auto hostSplit : hostport.at(3).split(',')) {
					host.append("-");
					// qDebug() << "missing " << serverMap[hostSplit.trimmed()];
					host.append(serverMap[hostSplit.trimmed()]);
				}
			}
			qDebug() << "DB: " << iter.key() << ":" << host + ":" + hostport.at(0) + "," + hostport.at(1) << " -> " << iter.value().kvNote;
		}
	}
	qDebug() << "Total server " << serverMap.size();
	qDebug() << "Total db " << dbMap.size();
	// return a.exec();

	return 0;
}
