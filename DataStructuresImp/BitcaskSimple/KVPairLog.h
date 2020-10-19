#ifndef KVPAIRLOG_H
#define KVPAIRLOG_H
#include <sys/types.h>
#include <cstdint>
#include <string>
#include <unordered_map>
template <typename KType, typename VType>
class KVPairLog {
private:
	std::unordered_map<KType, off_t> _inMemKOffsetHashMap;
	//
	std::string _dirPath;
	std::string _logFileName;
	int _currentWriteLogFileId;
	int _logFileFd;
	uint64_t _MAX_LOG_FILE_SIZE;  // may be 10MB per log file
	off_t _currentOffset;		  // use for write a new key
public:
	KVPairLog(const std::string& rootPath, const std::string logName);
	// write new record at currentOffset of the current write log file
	void writeKVPair(const KType& key, const VType& value);

	// read a key: locate current offset from inMem map
	// read at this offset from currentWriteFileID to lower id
	bool readKey(VType& retValue, const KType& key);

	// compaction a key-value update log (contain only the most recent value for each key)
	bool compactionLogSegment();
};
#endif	// KVPAIRLOG_H
