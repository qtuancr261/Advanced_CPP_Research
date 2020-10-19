#ifndef KVPAIRLOG_INL_H
#define KVPAIRLOG_INL_H
#include "KVPairLog.h"

template <typename KType, typename VType>
inline KVPairLog<KType, VType>::KVPairLog(const std::string &rootPath, const std::string logName)
	: _inMemKOffsetHashMap{},
	  _dirPath{rootPath},
	  _logFileName{logName},
	  _currentWriteLogFileId{0},
	  _logFileFd{-1},
	  _MAX_LOG_FILE_SIZE{10000000},
	  _currentOffset{0} {
	// <3 wait
}

template <typename KType, typename VType>
inline void KVPairLog<KType, VType>::writeKVPair(const KType &key, const VType &value) {
	// <3 wait
}

template <typename KType, typename VType>
inline bool KVPairLog<KType, VType>::readKey(VType &retValue, const KType &key) {
	// <3 wait
}

template <typename KType, typename VType>
inline bool KVPairLog<KType, VType>::compactionLogSegment() {
	// <3 wait
}

#endif	// KVPAIRLOG_INL_H
