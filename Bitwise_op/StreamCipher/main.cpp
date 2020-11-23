/*
 * Author: tuantq3
 * File: %{Cpp:License:FileName}
 *
 * Created on 12/7/2020
 */
#include <iostream>
#include <string>
#include "FeedBackRegister.h"
#include "google_benchmark/inc/benchmark.h"
#include <random>
using namespace std;
static void BM_StringCreation(benchmark::State& state) {
    for (auto _ : state) std::string empty_string;
}
static void BM_StringLen100Creation(benchmark::State& state) {
    for (auto _ : state) std::string len_sting(100, 'a');
}
static void BM_StringLen500Creation(benchmark::State& state) {
    for (auto _ : state) std::string len_sting(500, 'a');
}
static void BM_StringLen1000Creation(benchmark::State& state) {
    for (auto _ : state) std::string len_sting(1000, 'a');
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);
BENCHMARK(BM_StringLen100Creation);
BENCHMARK(BM_StringLen500Creation);
BENCHMARK(BM_StringLen1000Creation);

static void BM_StringCopy(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state)
    std::string copy(x);
}
BENCHMARK(BM_StringCopy);

static void BM_FeedbackRegister(benchmark::State& state) {
    std::default_random_engine _randEngine;
    std::uniform_int_distribution<uint64_t> dis;
    for (auto _ : state) {
        FeedBackRegister<uint64_t> _uintFSB{dis(_randEngine)};
    }
}
BENCHMARK(BM_FeedbackRegister);
BENCHMARK_MAIN();
// int main() {
//    FeedBackRegister<uint64_t> _fint{92388325570ull};
//    _fint.printAllState();
//    // edBackRegister<float> _float{3.14f};
//    // FeedBackRegister<string> _fstring{"rr"};
//}
