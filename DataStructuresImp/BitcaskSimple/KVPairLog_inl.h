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
      _logFileStat{},
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
        fstat(_logFileFd, &_logFileStat);
        std::clog << "log file stat " << _logFileStat.st_size << std::endl;
        // WAL log, get the last byte offset
        if (_logFileStat.st_size > 0) _currentOffset = lseek(_logFileFd, 0, SEEK_END);
    }
    // write a record | frame size | keysize | key | 4+ |value
    size_t kSize{0};
    if (std::is_fundamental<KType>::value) {
        kSize += sizeof(KType);
    } else if (std::is_class<KType>::value) {
        // kSize += key.size();
    }

    _inMemKOffsetHashMap[key] = _currentOffset;

    std::clog << _currentOffset << std::endl;
    _currentOffset += write(_logFileFd, &kSize, sizeof(size_t));
    off_t curOffset = lseek(_logFileFd, 0, SEEK_CUR);
    std::clog << curOffset << std::endl;
    std::clog << _currentOffset << std::endl;
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
    // or use: auto searchIt <3
    InMemMapConstIter searchIt = _inMemKOffsetHashMap.find(key);
    if (searchIt != _inMemKOffsetHashMap.end()) {
        off_t offset = searchIt->second;
        int fileFd{open(_logFileName.c_str(), O_RDONLY)};
        if (fileFd < 0) {
            std::cerr << "Open " << _logFileName << " failed";
            return false;
        }
        // lseek(fileFd, valueOffset, SEEK_SET);
        size_t kSize{};
        // read(fileFd, &kSize, sizeof(size_t));
        auto rsize = pread(fileFd, &kSize, sizeof(size_t), offset);
        if (rsize <= 0) {
            std::clog << "Read kSize failed: " << rsize;
            return false;
        }
        offset += rsize;
        std::clog << "kSize " << kSize << std::endl;

        KType rKey{};
        // read(fileFd, &rKey, kSize);
        rsize = pread(fileFd, &rKey, kSize, offset);
        if (rsize <= 0) {
            std::clog << "Read key failed: " << rsize;
            return false;
        }
        offset += rsize;
        std::clog << "rKey " << rKey << std::endl;

        size_t vSize{};
        rsize = pread(fileFd, &vSize, sizeof(size_t), offset);
        if (rsize <= 0) {
            std::clog << "Read vSize failed: " << rsize;
            return false;
        }
        offset += rsize;
        std::clog << "vSize " << vSize << std::endl;

        rsize = pread(fileFd, &retValue, vSize, offset);
        if (rsize < 0) {
            std::clog << "Read value failed " << rsize << std::endl;
        }
        std::clog << "value " << retValue << std::endl;

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
