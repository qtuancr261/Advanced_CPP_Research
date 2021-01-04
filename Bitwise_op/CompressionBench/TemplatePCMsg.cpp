#include "TemplatePCMsg.h"

TemplatePCMsg::TemplatePCMsg()
    : _dictBuffer{nullptr}
    , _msgPattern{}
    , _msgSamplesBuild{}
    , _msgSamplesBSizes{nullptr}
    , _numSamplesB{}
    , _msgSamplesTest{}
    , _compCtxPtr{ZSTD_createCCtx()}
    , _decompCtxPtr{ZSTD_createDCtx()}
    , _compDictPtr{nullptr}
    , _decompDictPtr{nullptr} {
    //
    _randEngine.seed(_randEngine());
}

TemplatePCMsg::~TemplatePCMsg() {
    if (_dictBuffer) {
        free(_dictBuffer);
    }

    ZSTD_freeCCtx(_compCtxPtr);
    ZSTD_freeDCtx(_decompCtxPtr);
}

void TemplatePCMsg::readPatternFromFile(std::string fileName) {
    _msgPattern.clear();
    // 1: cash
    // 2: id
    // 3: img id
    // 4: platform
    QString lineText("");
    QFile patternFile{fileName.c_str()};
    if (patternFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream readStream(&patternFile);
        while (readStream.readLineInto(&lineText)) {
            _msgPattern.append(lineText);
        }
    }

    patternFile.close();
}

void TemplatePCMsg::genMsgTestFromPattern(size_t numMsg) {
    if (_msgPattern.isEmpty()) {
        qDebug() << "Empty pattern!";
        return;
    }
    std::uniform_int_distribution<uint64_t> dis;
    _msgSamplesTest.clear();
    _msgSamplesTest.reserve(numMsg);
    for (size_t i{}; i < numMsg; ++i) {
        QString genMsg = _msgPattern.arg(dis(_randEngine)).arg(numMsg).arg(dis(_randEngine)).arg(platformTest[i & 7]);
        _msgSamplesTest.push_back(genMsg.toStdString());
    }
}

void TemplatePCMsg::genMsgBuildFromPattern(size_t numMsg) {
    if (_msgPattern.isEmpty()) {
        qDebug() << "Empty pattern!";
        return;
    }

    if (!_msgSamplesBSizes) {
        if (numMsg <= TRAIN_SAMPLES_SIZE) {
            _msgSamplesBSizes.reset(new size_t[TRAIN_SAMPLES_SIZE]);
            _numSamplesB = numMsg;
        } else {
            _msgSamplesBSizes.reset(new size_t[numMsg]);
            _numSamplesB = numMsg;
        }
    } else {
        if (numMsg <= TRAIN_DICT_SIZE) {
            _numSamplesB = numMsg;
        } else {
            _msgSamplesBSizes.reset(new size_t[numMsg]);
            _numSamplesB = numMsg;
        }
    }

    std::uniform_int_distribution<uint64_t> dis;
    _msgSamplesBuild.clear();

    for (size_t i{}; i < _numSamplesB; ++i) {
        QString genMsg = _msgPattern.arg(dis(_randEngine)).arg(numMsg).arg(dis(_randEngine)).arg(platformBuild[i & 3]);
        std::string tmpStr = genMsg.toStdString();
        _msgSamplesBuild.append(tmpStr);
        _msgSamplesBSizes[i] = tmpStr.size();
    }
}

void TemplatePCMsg::trainDict() {
    // make sure we have samples for build
    if (_msgSamplesBuild.empty()) {
        genMsgBuildFromPattern(TRAIN_SAMPLES_SIZE);
    }

    // build dict
    if (!_dictBuffer) {
        _dictBuffer = malloc(TRAIN_DICT_SIZE);
    }
    size_t dictSize{ZDICT_trainFromBuffer(_dictBuffer, TRAIN_DICT_SIZE, _msgSamplesBuild.data(), _msgSamplesBSizes.get(), _numSamplesB)};
    qDebug() << "Train dict size: " << dictSize;

    _compDictPtr = ZSTD_createCDict(_dictBuffer, dictSize, ZSTD_fast);
    _decompDictPtr = ZSTD_createDDict(_dictBuffer, dictSize);
}

ZSTD_CCtx *TemplatePCMsg::getCompCtx() const { return _compCtxPtr; }

ZSTD_DCtx *TemplatePCMsg::getDecompCtx() const { return _decompCtxPtr; }

size_t TemplatePCMsg::compressUseDict(std::string &dst, const std::string &src) {}

size_t TemplatePCMsg::decompressUseDict(std::string &dst, const std::string &src) {}
