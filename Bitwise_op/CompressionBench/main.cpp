/*
 * Author: tuantq3
 * File: %{Cpp:License:FileName}
 *
 * Created on 12/7/2020
 */
#include <lz4.h>
#include <snappy-c.h>
#include <snappy.h>
#include <zdict.h>
#include <zstd.h>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <cstring>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include "google_benchmark/inc/benchmark.h"

// ZSTD tips: In general, a reasonable dictionary has a size of ~ 100 KB
#define ZSTD_DICT_DEF_SIZE 100000

using namespace std;
std::default_random_engine randEngine;

QString platform[]{"linux", "win", "ios", "android"};
void zenString(std::string& result, size_t len, bool isPrintable) {
	int min = isPrintable ? 32 : 0;
	int max = isPrintable ? 126 : 255;
	std::uniform_int_distribution<char> dis(min, max);
	result.resize(len);
	for (int i{}; i < len; ++i) {
		result[i] = (dis(randEngine));
	}
}

void readMsgPattern(std::string& msgPattern) {
	qDebug() << "read pattern";
	QFile msgPatternFile("zns_msgp_pattern.html");
	QString pattern;
	QString line("");
	if (msgPatternFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream readStream(&msgPatternFile);
		while (readStream.readLineInto(&line)) {
			pattern.append(line);
			line.clear();
		}
	}
	// 1: cash
	// 2: id
	// 3: img id
	// 4: platform
	// QString genMsg = pattern.arg(500).arg(2611996).arg(20202231).arg("linux");
	msgPattern = pattern.toStdString();
	// std::cout << msgPattern;
	// qDebug() << genMsg;
}

void genMsgFromPattern(std::string& samples, size_t* samplesSizes, const std::string& pattern, size_t numMsg) {
	qDebug() << "gen msg from pattern";
	uniform_int_distribution<uint32_t> dis;
	QString patternQ{QString::fromStdString(pattern)};

	for (size_t i{}; i < numMsg; ++i) {
		QString genMsg = patternQ.arg(dis(randEngine)).arg(numMsg).arg(dis(randEngine)).arg(platform[i & 3]);
		std::string tmpStr = genMsg.toStdString();
		samplesSizes[i] = tmpStr.size();
		samples.append(tmpStr);
	}
}

void readMsgTemplate(std::string& msg) {
	QFile msgTempFile("zns_msgp.245111.html");
	if (msgTempFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream readStream(&msgTempFile);
		QString line("");
		while (readStream.readLineInto(&line)) {
			// qDebug() << line;
			msg.append(line.toStdString());
		}
	}
}
static void BM_StringCreation(benchmark::State& state) {
	for (auto _ : state) std::string empty_string;
}

// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

static void BM_StringCopy(benchmark::State& state) {
	std::string x = "hello";
	for (auto _ : state) std::string copy(x);
}
// BENCHMARK(BM_StringCopy);

// memcpy as default ratio

// Begin benchmark
// BENCHMARK_MAIN();
std::string example(1000, 'z');
std::string target(4096, 'a');
std::string decompressTarget(1000, 'b');
int sizeCompress{};
int sizeDecompress{};
int sizeCompressBound{};
size_t sizeCBound{};
size_t sizeDBound{};
std::unique_ptr<char[]> targetData{nullptr};
std::unique_ptr<char[]> decompressData{nullptr};

static void BM_memcpy(benchmark::State& state) {
	example.clear();
	readMsgTemplate(example);
	target.resize(example.size());
	for (auto _ : state) {
		memcpy(target.data(), example.data(), example.size());
	}
	state.SetBytesProcessed((int64_t)state.iterations() * example.size());
}

BENCHMARK(BM_memcpy);

static void BM_LZ4_compress_default(benchmark::State& state) {
	example.clear();
	readMsgTemplate(example);
	sizeCompressBound = LZ4_compressBound(example.size());
	target.resize(sizeCompressBound);
	for (auto _ : state) {
		sizeCompress = LZ4_compress_default(example.data(), target.data(), example.size(), target.size());
	}
	state.SetBytesProcessed((int64_t)state.iterations() * example.size());
}

BENCHMARK(BM_LZ4_compress_default);

static void BM_LZ4_decompress_safe(benchmark::State& state) {
	// 4kB
	// cout << "size " << sizeCompress;
	decompressTarget.resize(example.size());
	target.resize(sizeCompress);
	for (auto _ : state) {
		sizeDecompress = LZ4_decompress_safe(target.data(), decompressTarget.data(), target.size(), decompressTarget.size());
	}
	state.SetBytesProcessed((int64_t)state.iterations() * example.size());
	// cout << "Size decomp " << sizeDecompress << endl;
}

BENCHMARK(BM_LZ4_decompress_safe);

static void BM_snappy_compress(benchmark::State& state) {
	example.clear();
	readMsgTemplate(example);
	target.clear();
	for (auto _ : state) {
		sizeCompress = snappy::Compress(example.data(), example.size(), &target);
	}
	state.SetBytesProcessed((int64_t)state.iterations() * example.size());
}

BENCHMARK(BM_snappy_compress);

static void BM_snappy_decompress(benchmark::State& state) {
	decompressTarget.clear();
	for (auto _ : state) {
		sizeDecompress = snappy::Uncompress(target.data(), target.size(), &decompressTarget);
	}
	state.SetBytesProcessed((int64_t)state.iterations() * example.size());
}

BENCHMARK(BM_snappy_decompress);

static void BM_snappy_c_compress(benchmark::State& state) {
	example.clear();
	readMsgTemplate(example);
	sizeCompressBound = snappy_max_compressed_length(example.size());
	// char* targetData{new char[sizeCompressBound]};
	targetData.reset(new char[sizeCompressBound]);
	for (auto _ : state) {
		sizeCBound = sizeCompressBound;
		if (snappy_compress(example.data(), example.size(), targetData.get(), &sizeCBound) != SNAPPY_OK) state.SetBytesProcessed(0);
	}
	state.SetBytesProcessed((int64_t)state.iterations() * example.size());
}

BENCHMARK(BM_snappy_c_compress);

static void BM_snappy_c_decompress(benchmark::State& state) {
	if (snappy_uncompressed_length(targetData.get(), sizeCBound, &sizeDBound) != SNAPPY_OK) {
		state.SetBytesProcessed(0);
		return;
	}
	sizeDecompress = sizeDBound;
	// char* decomData{new char[sizeDBound]};
	decompressData.reset(new char[sizeDBound]);
	for (auto _ : state) {
		if (snappy_uncompress(targetData.get(), sizeCBound, decompressData.get(), &sizeDBound) != SNAPPY_OK) {
			state.SetBytesProcessed(0);
		}
		sizeDBound = sizeDecompress;
	}
	state.SetBytesProcessed((int64_t)state.iterations() * example.size());
}

BENCHMARK(BM_snappy_c_decompress);

static void BM_zstd_compress(benchmark::State& state) {
	example.clear();
	readMsgTemplate(example);
	target.clear();
	sizeCompressBound = ZSTD_compressBound(example.size());
	target.resize(sizeCompressBound);
	for (auto _ : state) {
		sizeCompress = ZSTD_compress(target.data(), sizeCompressBound, example.data(), example.size(), 1);
	}
	target.resize(sizeCompress);
	state.SetBytesProcessed((int64_t)state.iterations() * example.size());
}

BENCHMARK(BM_zstd_compress);

static void BM_zstd_decompress(benchmark::State& state) {
	decompressTarget.clear();
	decompressTarget.resize(ZSTD_getFrameContentSize(target.data(), target.size()));
	for (auto _ : state) {
		sizeDecompress = ZSTD_decompress(decompressTarget.data(), decompressTarget.size(), target.data(), target.size());
		if (ZSTD_isError(sizeDecompress)) {
			qDebug() << ZSTD_getErrorName(sizeDecompress);
			return;
		}
	}
	state.SetBytesProcessed((int64_t)state.iterations() * example.size());
}

BENCHMARK(BM_zstd_decompress);

static void BM_zstd_compress_context(benchmark::State& state) {
	// same compress ratio with zstd_compress
	// optimize speed / resource
	example.clear();
	readMsgTemplate(example);
	target.clear();
	ZSTD_CCtx* comContext = ZSTD_createCCtx();
	sizeCompressBound = ZSTD_compressBound(example.size());
	target.resize(sizeCompressBound);
	for (auto _ : state) {
		// sizeCompress = ZSTD_compress((void*)target.data(), target.size(), (void*)example.data(), example.size(), 1);
		sizeCompress = ZSTD_compressCCtx(comContext, target.data(), sizeCompressBound, example.data(), example.size(), 1);
	}
	target.resize(sizeCompress);
	state.SetBytesProcessed((int64_t)state.iterations() * example.size());
	ZSTD_freeCCtx(comContext);
}

BENCHMARK(BM_zstd_compress_context);

static void BM_zstd_decompress_context(benchmark::State& state) {
	// same decompress ratio with zstd_decompress
	// optimize speed / resource
	decompressTarget.clear();
	decompressTarget.resize(ZSTD_getFrameContentSize(target.data(), target.size()));
	ZSTD_DCtx* decomContext = ZSTD_createDCtx();
	for (auto _ : state) {
		// sizeDecompress = ZSTD_decompress(decompressTarget.data(), decompressTarget.size(), target.data(), target.size());
		sizeDecompress = ZSTD_decompressDCtx(decomContext, decompressTarget.data(), decompressTarget.size(), target.data(), target.size());
		if (ZSTD_isError(sizeDecompress)) {
			qDebug() << ZSTD_getErrorName(sizeDecompress);
			return;
		}
	}
	state.SetBytesProcessed((int64_t)state.iterations() * example.size());
	ZSTD_freeDCtx(decomContext);
}

BENCHMARK(BM_zstd_decompress_context);

// BENCHMARK_MAIN();
int main() {
	//	example.clear();
	//	cout << "LZ4" << endl;
	//	readMsgTemplate(example);
	//	cout << example.size() << endl;
	//	sizeCompressBound = LZ4_compressBound(example.size());
	//	cout << "Bound size: " << sizeCompressBound << endl;
	//	target.resize(sizeCompressBound);
	//	cout << target.size() << endl;
	//	sizeCompress = LZ4_compress_default(example.data(), target.data(), example.size(), target.size());
	//	target.resize(sizeCompress);
	//	cout << sizeCompress << endl;
	//	decompressTarget.resize(example.size());
	//	sizeDecompress = LZ4_decompress_safe(target.data(), decompressTarget.data(), target.size(), decompressTarget.size());
	//	cout << sizeDecompress << endl;

	//	cout << "Snappy " << SNAPPY_VERSION << endl;
	//	cout << snappy::Compress(example.data(), example.size(), &target) << endl;
	//	cout << snappy::Uncompress(target.data(), target.size(), &decompressTarget) << endl;
	//	cout << decompressTarget.size() << endl;
	//	assert(example == decompressTarget);

	//	example.clear();
	//	cout << "Snappy_C " << SNAPPY_VERSION << endl;
	//	readMsgTemplate(example);
	//	sizeCBound = snappy_max_compressed_length(example.size());
	//	cout << sizeCBound << endl;
	//	char* targetData{new char[sizeCBound]};
	//	if (snappy_compress(example.data(), example.size(), targetData, &sizeCBound) != SNAPPY_OK) {
	//		cout << "snappy_c compress failed: buffer too small " << example.size() << " : " << sizeCBound << endl;
	//	} else {
	//		cout << "snappy_c compress success " << example.size() << " : " << sizeCBound << endl;
	//	}
	//	delete[] targetData;

	//	cout << "ZSTD " << ZSTD_versionNumber() << endl;
	//	sizeCompressBound = ZSTD_compressBound(example.size());
	//	cout << "Bound size " << sizeCompressBound << endl;
	//	target.resize(sizeCompressBound);
	//	sizeCompress = ZSTD_compress((void*)target.data(), target.size(), (void*)example.data(), example.size(), 1);
	//	cout << "Comp size " << sizeCompress << endl;
	//	cout << "decomp size " << ZSTD_getFrameContentSize(target.data(), target.size()) << endl;
	//	target.resize(sizeCompress);
	//	sizeDecompress = ZSTD_decompress((void*)decompressTarget.data(), decompressTarget.size(), (void*)target.data(), target.size());
	//	cout << "Decomp size " << sizeDecompress << endl;
	//	assert(example == decompressTarget);

	//	cout << "ZSTD use context " << ZSTD_versionNumber() << endl;
	//	ZSTD_CCtx* comCtx = ZSTD_createCCtx();
	//	sizeCompressBound = ZSTD_compressBound(example.size());
	//	cout << "Bound size " << sizeCompressBound << endl;
	//	target.resize(sizeCompressBound);
	//	sizeCompress = ZSTD_compressCCtx(comCtx, target.data(), target.size(), example.data(), example.size(), 1);
	//	cout << "Comp size " << sizeCompress << endl;
	//	cout << "decomp size " << ZSTD_getFrameContentSize(target.data(), target.size()) << endl;
	//	ZSTD_DCtx* decomCtx = ZSTD_createDCtx();
	//	target.resize(sizeCompress);
	//	sizeDecompress = ZSTD_decompressDCtx(decomCtx, decompressTarget.data(), sizeDecompress, target.data(), target.size());
	//	cout << "Decomp size " << sizeDecompress << endl;
	//	assert(example == decompressTarget);

	// ZSTD use dict
	std::string pattern;
	readMsgPattern(pattern);

	void* dictBuffer{malloc(ZSTD_DICT_DEF_SIZE)};
	size_t* samplesSizes{new size_t[3000]};
	std::string samples;
	if (dictBuffer) {
		// a few thousands samples
		genMsgFromPattern(samples, samplesSizes, pattern, 3000);
		// build dict
		size_t dictTrainedSize = ZDICT_trainFromBuffer(dictBuffer, ZSTD_DICT_DEF_SIZE, samples.data(), samplesSizes, 3000);
		if (ZDICT_isError(dictTrainedSize)) {
			qDebug() << "Train dict failed: " << dictTrainedSize;
		} else {
			qDebug() << "Train dict completed: " << dictTrainedSize;
			// ok, let's pick some samples and compress - decompress using dict
			qDebug() << "template size " << pattern.size();
			ZSTD_CDict* cdict = ZSTD_createCDict(dictBuffer, dictTrainedSize, 1);
			ZSTD_DDict* ddict = ZSTD_createDDict(dictBuffer, dictTrainedSize);
			if (cdict == NULL || ddict == NULL) {
				qDebug() << "ZSTD_createCDict | ZSTD_createDDict from trained dict buff is failed ";
			} else {
				ZSTD_CCtx* comCtx = ZSTD_createCCtx();
				ZSTD_DCtx* decomCtx = ZSTD_createDCtx();
				std::string targetCompress;
				std::string targetDecompress;
				char* data = samples.data();
				for (int i{}; i < 20; ++i) {
					// compress
					targetCompress.clear();
					sizeCompressBound = ZSTD_compressBound(samplesSizes[i]);
					targetCompress.resize(sizeCompressBound);

					sizeCompress = ZSTD_compress_usingCDict(comCtx, targetCompress.data(), sizeCompressBound, data, samplesSizes[i], cdict);
					// must do
					targetCompress.resize(sizeCompress);
					// decompress
					targetDecompress.clear();
					targetDecompress.resize(ZSTD_getFrameContentSize(targetCompress.data(), targetCompress.size()));
					auto expectedDictID = ZSTD_getDictID_fromDDict(ddict);
					auto actualDictID = ZSTD_getDictID_fromFrame(targetCompress.data(), targetCompress.size());
					if (expectedDictID != actualDictID) {
						qDebug() << "Mismatch dictID";
					}
					sizeDecompress = ZSTD_decompress_usingDDict(
						decomCtx, targetDecompress.data(), targetDecompress.size(), targetCompress.data(), targetCompress.size(), ddict);
					if (ZSTD_isError(sizeDecompress)) {
						qDebug() << ZSTD_getErrorName(sizeDecompress);
					}
					assert(samplesSizes[i] == sizeDecompress);
					qDebug() << samplesSizes[i] << " -> " << sizeCompress << " -> " << sizeDecompress;

					//----------------------
					data += samplesSizes[i];
				}
				ZSTD_freeCCtx(comCtx);
				ZSTD_freeDCtx(decomCtx);
			}
			ZSTD_freeCDict(cdict);
			ZSTD_freeDDict(ddict);
		}

	} else {
		qDebug() << "alloct dictBuffer failed ";
	}

	free(dictBuffer);
	delete[] samplesSizes;
	return 0;
}
