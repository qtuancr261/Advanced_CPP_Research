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
using namespace std;
static void BM_StringCreation(benchmark::State& state) {
    for (auto _ : state) std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);
BENCHMARK_MAIN();
// int main() {
//    FeedBackRegister<uint64_t> _fint{92388325570ull};
//    _fint.printAllState();
//    // edBackRegister<float> _float{3.14f};
//    // FeedBackRegister<string> _fstring{"rr"};
//}
