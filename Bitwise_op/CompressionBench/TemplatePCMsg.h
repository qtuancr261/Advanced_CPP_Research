#ifndef TEMPLATEPCMSG_H
#define TEMPLATEPCMSG_H

#include <zdict.h>
#include <zstd.h>

#include <memory>
#include <random>
#include <string>
#include <vector>

#include <QDebug>
#include <QFile>
#include <QTextStream>

#define TRAIN_DICT_SIZE 100000	 // recommended by zstd: 100KB
#define TRAIN_SAMPLES_SIZE 3000	 //

class TemplatePCMsg {
private:
    void* _dictBuffer;
    QString _msgPattern;
    // samples for building dict
    std::string _msgSamplesBuild;
    // size_t* _msgSamplesBuildSize;
    std::unique_ptr<size_t[]> _msgSamplesBSizes;
    size_t _numSamplesB;
    // samples for testing compress - decompress
    std::vector<std::string> _msgSamplesTest;

    // Compress - decompress context
    ZSTD_CCtx* _compCtxPtr;
    ZSTD_DCtx* _decompCtxPtr;

    // Compress - decompress dict
    ZSTD_CDict* _compDictPtr;
    ZSTD_DDict* _decompDictPtr;

    //
    std::default_random_engine _randEngine;
    static inline std::random_device _randSeed;

    //
    const static inline QString platformBuild[]{"linux", "android", "ios", "generic"};
    const static inline QString platformTest[]{"android-8", "android-9", "android-10", "win 7", "win 10", "ios-11", "ios-12", "ios-13"};

public:
    TemplatePCMsg();
    ~TemplatePCMsg();

    void readPatternFromFile(std::string fileName);

    //  samples will contain more information than samples build
    void genMsgTestFromPattern(size_t numMsg);

    void genMsgBuildFromPattern(size_t numMsg);

    void trainDictBuffer();

    ZSTD_CCtx* getCompCtx() const;
    ZSTD_DCtx* getDecompCtx() const;
};

#endif	// TEMPLATEPCMSG_H
