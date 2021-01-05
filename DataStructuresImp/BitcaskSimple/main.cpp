#include <iostream>
#include <string>
#include "KVPairLog.h"
#include "KVPairLog_inl.h"
using namespace std;
std::string rootPath{"."};
std::string logName{"idName"};
class A {};

int main() {
	KVPairLog<int, int> _idNameLogs{rootPath, logName};
    int key{2610};
    int value{2020};
    _idNameLogs.writeKVPair(key, value);
    int readValue{};
    _idNameLogs.readKey(readValue, key);
    return 0;
}
