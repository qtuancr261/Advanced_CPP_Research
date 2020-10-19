#include <iostream>
#include <string>
#include "KVPairLog.h"
#include "KVPairLog_inl.h"
using namespace std;
std::string rootPath{"."};
std::string logName{"idName"};
int main() {
	KVPairLog<int, int> _idNameLogs{rootPath, logName};
	_idNameLogs.compactionLogSegment();
	return 0;
}
