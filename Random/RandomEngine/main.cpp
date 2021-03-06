/*
 * Author: tuantq3
 * File: main.cpp
 *
 * Created on 15/8/2019
 *
 * Testing stl generating random numbers
 */

#include <benchmark/benchmark.h>
#include <cstring>
#include <ctime>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
using std::copy;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::rand;
using std::random_device;
using std::seed_seq;
using std::srand;
using std::string;
using std::time;
using std::uniform_int_distribution;
using std::vector;

#define MAX_SESSION_CURSOR ((uint16_t(int16_t(-1)) / 15) * 15 - 1)
#define seperatorBeginEnd cout << endl << "-------------------------------------------------------------" << endl
#define src(i) #i
#define INIT_BENCHMARK_USER()                                           \
    ::benchmark::Initialize(&argc, argv);                               \
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1; \
    ::benchmark::RunSpecifiedBenchmarks()

void testObtaningRandomSeeds(int numSeeds) {
    // std::random_device is a uniformly-distributed integer random number generator
    // that produces non-deteministic random numbers
    // Use std::random_device as a seeds generator
    //
    random_device randDev{};
    cout << "Min rand value: " << randDev.min() << endl;
    cout << "Max rand value: " << randDev.max() << endl;
    // the max rand value is equal to std::numeric_limits<unsigned int>::max()
    // if the implementation is using a random number engine and not a non-deteministic source entropy value is equal to 0
    for (int iseed = 0; iseed < numSeeds; ++iseed) {
        cout << "Rand seed: " << randDev() << endl;
    }
    cout << "Entropy " << randDev.entropy() << endl;
    seperatorBeginEnd;
}
void genSeedSequences(seed_seq& initSeedSeq, const string& title, size_t numGenValues = 10) {
    vector<uint> ranVec(numGenValues, 0);
    // You will get  a wide range of 32-bit integers generated
    // Regardless of how you create the seed_seq object
    // the generate() member produces as many different values as are necessary to fill the range you specify
    initSeedSeq.generate(std::begin(ranVec), std::end(ranVec));
    // You can call generate() as many times as you like
    // The values in a sequence produced by generate() depends on the length of the sequence
    // Sequences of a given length will be the same per generate() call
    // Sequences of different lengths will contain different values.

    cout << title << endl;
    copy(std::begin(ranVec), std::end(ranVec), std::ostream_iterator<uint>{cout, " - "});
    seperatorBeginEnd;
}

void testSeedSeq(size_t numGenValue = 10) {
    seed_seq seedSeq_1;  // default constructor
    genSeedSequences(seedSeq_1, "seedSeq_1 - default constructor ");
    genSeedSequences(seedSeq_1, "seedSeq_1 - default constructor AGAIN");
    genSeedSequences(seedSeq_1, "seedSeq_1 - default constructor AGAIN (different gen num: 5)", 5);
    seed_seq seedSeq_2{2610, 1996, 2018, 12};
    genSeedSequences(seedSeq_2, "seedSeq_2 - consecutive int ");
    genSeedSequences(seedSeq_2, "seedSeq_2 - consecutive int AGAIN");
    genSeedSequences(seedSeq_2, "seedSeq_2 - consecutive int AGAIN (different gen num: 4)", 4);
    genSeedSequences(seedSeq_2, "seedSeq_2 - consecutive int AGAIN");
    genSeedSequences(seedSeq_2, "seedSeq_2 - consecutive int AGAIN (different gen num: 12)", 12);
    random_device rd;
    seed_seq seedSeq_3{rd(), rd()};
    // if we use argument value create by std::random_device for seed_seq constructor
    // the sequences will be different per program excution
    genSeedSequences(seedSeq_3, "seedSeq_3 - use random_device");
    genSeedSequences(seedSeq_3, "seedSeq_3 - use random_device AGAIN (different gen num: 8)", 8);
    genSeedSequences(seedSeq_3, "seedSeq_3 - use random_device AGAIN (different gen num: 16)", 16);
    vector<int> initValue{2610, 1996, 2018, 12};
    // the same argument values to the seed_seq constructor the same sequences you will get when call generate() per program execution (same length as well)
    seed_seq seedSeq_4(std::begin(initValue), std::end(initValue));
    genSeedSequences(seedSeq_4, "seedSeq_5 - use a range (the same as seedSeq_2)");
    initValue.push_back(2000);
    seed_seq seedSeq_5(std::begin(initValue), std::end(initValue));
    genSeedSequences(seedSeq_5, "seedSeq_5 - use a range ");
}

void testDefaultRandomNumGenerator() {
    seperatorBeginEnd;
    // std::default_random_engine is a general-purpose of random uintegers
    default_random_engine randEngine1;        // default seed (the random sequences will always be the same)
    default_random_engine randEngine2{2610};  // supply seed by yourself but still fixed

    random_device randDev;
    default_random_engine randEngine3{randDev()};  // use seed created by random_device -> the sequence will be a suprise everytime
    seed_seq seedSeq{randDev(), randDev(), randDev()};
    default_random_engine randEngine4{seedSeq};  // or we could use a seed_seq as parameter

    // Let use some distribution class
    uniform_int_distribution<int64_t> uIntDis;
    cout << endl << src(uniform_int_distribution<int64_t>) << " range random: [" << uIntDis.min() << " - " << uIntDis.max() << "]" << endl;
    seperatorBeginEnd;
}

static void BM_memcpy(benchmark::State& state) {
    char* src{new char[state.range(0)]};
    char* dst{new char[state.range(0)]};
    memset(src, 'z', state.range(0));
    for (auto _ : state) {
        memcpy(dst, src, state.range(0));
    }
    state.SetBytesProcessed(static_cast<int64_t>(state.range(0) * state.iterations()));
    state.SetItemsProcessed(state.iterations());
    delete[] src;
    delete[] dst;
}
static void BM_rand(benchmark::State& state) {
    std::srand(time(nullptr));
    for (auto _ : state) {
        int randNum = rand();
    }
    //    while (state.KeepRunning()) {
    //        int randNum = rand();
    //    }
}  // BENCHMARK(BM_memcpy)->Arg(8)->Arg(16)->Arg(32)->Arg(64)->Arg(128)->Arg(512);

static void BM_random_device(benchmark::State& state) {
    random_device randDev;
    for (auto _ : state) {
        int randNum = randDev();
    }
    //    while (state.KeepRunning()) {
    //        int randNum = randDev();
    //    }
}
// BENCHMARK(BM_memcpy)->Range(1 << 3, 1 << 10);
BENCHMARK(BM_rand);
BENCHMARK(BM_random_device);
// BENCHMARK_MAIN();

int main(int argc, char* argv[]) {
    // gen single seed value
    testObtaningRandomSeeds(10);
    // gen seed sequences
    testSeedSeq();
    // test random engine with specific distributions
    testDefaultRandomNumGenerator();
    INIT_BENCHMARK_USER();
    return 0;
}
