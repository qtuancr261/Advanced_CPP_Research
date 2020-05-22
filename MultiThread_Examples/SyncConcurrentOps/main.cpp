/*
 * Author: tuantq3
 * File: %{Cpp:License:FileName}
 *
 * Created on 19/5/2020
 */
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <iterator>
#include <mutex>
#include <queue>
#include <random>
#include <thread>
std::random_device randSeed;
std::mutex mutexQueue;

std::queue<uint32_t> jobsQueue;
std::condition_variable jobCondition;
void initJobGen(std::default_random_engine& randEng, int seed) {
    std::cout << "Thread seed: " << seed << std::endl;
    randEng.seed(seed);
}
void prepareJobs(int seed) {
    static thread_local std::default_random_engine randEng;
    static thread_local std::once_flag flagInit;
    try {
        std::call_once(flagInit, initJobGen, randEng, seed);
    } catch (std::exception& exp) {
        std::cout << exp.what();
    }
    static thread_local std::uniform_int_distribution<uint32_t> randDis;
    while (true) {
        uint32_t newJobs{randDis(randEng)};
        std::cout << "JobID: " << newJobs << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main() {
    std::vector<uint32_t> threadSeeds(std::thread::hardware_concurrency());
    auto toDaySeed{randSeed()};
    std::cout << "Today seed is : " << toDaySeed << std::endl;
    std::seed_seq seedSeq{toDaySeed};
    seedSeq.generate(std::begin(threadSeeds), std::end(threadSeeds));
    std::copy(std::begin(threadSeeds), std::end(threadSeeds), std::ostream_iterator<uint32_t>(std::cout, " | "));
    prepareJobs(threadSeeds[0]);
    return 0;
}
