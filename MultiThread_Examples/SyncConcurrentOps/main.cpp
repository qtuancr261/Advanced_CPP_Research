/*
 * Author: tuantq3
 * File: %{Cpp:License:FileName}
 *
 * Created on 19/5/2020
 */
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>
std::random_device randSeed;
std::mutex mutexQueue;
std::uniform_int_distribution<uint32_t> randDis;
std::default_random_engine randEngine;
std::queue<uint32_t> jobsQueue;
std::condition_variable jobCondition;
std::once_flag jobGenInit;
void initJobGen(int a) {
    uint32_t seed{randSeed()};
    std::cout << "Today seed: " << seed << std::endl;
    randEngine.seed(seed);
}
void prepareJobs() {
    try {
        std::call_once(jobGenInit, initJobGen, 10);
    } catch (std::exception& exp) {
        std::cout << exp.what();
    }

    while (true) {
        uint32_t newJobs{randDis(randEngine)};
        std::cout << "JobID: " << newJobs << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main() {
    prepareJobs();
    return 0;
}
