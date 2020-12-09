/*
 * Author: tuantq3
 * File: %{Cpp:License:FileName}
 *
 * Created on 12/7/2020
 */
#include <lz4.h>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <cstring>
#include <iostream>
#include <random>
#include <string>
#include "google_benchmark/inc/benchmark.h"
using namespace std;
std::default_random_engine randEngine;
void zenString(std::string& result, size_t len, bool isPrintable) {
	int min = isPrintable ? 32 : 0;
	int max = isPrintable ? 126 : 255;
	std::uniform_int_distribution<char> dis(min, max);
	result.resize(len);
	for (int i{}; i < len; ++i) {
		result[i] = (dis(randEngine));
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
BENCHMARK(BM_StringCopy);

// memcpy as default ratio
static void BM_memcpy(benchmark::State& state) {}

// Begin benchmark
// BENCHMARK_MAIN();
std::string example(1000, 'z');
std::string target(4096, 'a');
std::string decompressTarget(1000, 'b');
int sizeCompress{};
int sizeDecompress{};
int sizeCompressBound{};

static void BM_LZ4_compress_default(benchmark::State& state) {
	example.clear();
	readMsgTemplate(example);
	sizeCompressBound = LZ4_compressBound(example.size());
	target.resize(sizeCompressBound);
	for (auto _ : state) {
		sizeCompress = LZ4_compress_default(example.data(), target.data(), example.size(), target.size());
	}
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
	// cout << "Size decomp " << sizeDecompress << endl;
}

BENCHMARK(BM_LZ4_decompress_safe);

BENCHMARK_MAIN();
// int main() {
//	example.clear();
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
//	return 0;
//}
