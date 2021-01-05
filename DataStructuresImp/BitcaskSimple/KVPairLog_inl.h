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
    static_assert(!std::is_pointer<KType>::value, "KType not support pointer");
    static_assert(!std::is_pointer<VType>::value, "VType not support pointer");
}

template <typename KType, typename VType>
inline KVPairLog<KType, VType>::~KVPairLog() {
    close(_logFileFd);
}

template <typename KType, typename VType>
inline void KVPairLog<KType, VType>::writeKVPair(const KType &key, const VType &value) {
	// <3 wait
    if (_logFileFd < 0) {
        _logFileName.append("_").append(std::to_string(_currentWriteLogFileId));
        _logFileFd = open(_logFileName.c_str(), O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
        if (_logFileFd < 0) {
            std::cerr << "Open " << _logFileName << " failed \n";
            return;
        }
    }
    // write a record | frame size | keysize | key | 4+ |value
    size_t kSize{0};
    if (std::is_fundamental<KType>::value) {
        kSize += sizeof(KType);
    } else if (std::is_class<KType>::value) {
        // kSize += key.size();
    }

    _inMemKOffsetHashMap[key] = _currentOffset;
    _currentOffset += write(_logFileFd, &kSize, sizeof(size_t));
    _currentOffset += write(_logFileFd, &key, kSize);
    std::clog << "Write " << _currentOffset << std::endl;
    size_t vSize{0};
    if (std::is_fundamental<VType>::value) {
        vSize += sizeof(VType);
    } else if (std::is_class<VType>::value) {
        // vSize += key.size();
    }

    _currentOffset += write(_logFileFd, &vSize, sizeof(size_t));
    _currentOffset += write(_logFileFd, &value, vSize);
    std::clog << "Write " << _currentOffset << std::endl;
}

template <typename KType, typename VType>
inline bool KVPairLog<KType, VType>::readKey(VType &retValue, const KType &key) {
	// <3 wait
    auto searchIt = _inMemKOffsetHashMap.find(key);
    if (searchIt != _inMemKOffsetHashMap.end()) {
        //        off_t valueOffset = searchIt->second();
        off_t valueOffset = 0;
        int fileFd{open(_logFileName.c_str(), O_RDONLY)};
        if (fileFd < 0) {
            std::cerr << "Open " << _logFileName << " failed";
            return false;
        }
        lseek(fileFd, valueOffset, SEEK_SET);
        size_t kSize{};
        read(fileFd, &kSize, sizeof(size_t));
        std::clog << "kSize " << kSize;
	KType rKey{};
        read(fileFd, &rKey, kSize);
        std::clog << "rKey " << rKey;
        close(fileFd);
        return true;
    }
    return false;
}

template <typename KType, typename VType>
inline bool KVPairLog<KType, VType>::compactionLogSegment() {
	// <3 wait
}

#endif  // KVPAIRLOG_INL_H
