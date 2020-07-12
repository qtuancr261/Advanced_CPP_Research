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
#include <atomic>
#include "ThreadSafeQueue.h"
std::random_device randSeed;
std::mutex mutexJobsQueue;

std::queue<uint32_t> jobsQueue;
std::condition_variable jobCondition;
std::atomic<uint64_t> totalProcessJobs{};
const uint64_t MAX_JOBS = 70000000ull;
void initJobGen(std::default_random_engine& randEng, uint32_t seed) {
    std::cout << "\nThread seed: " << seed << std::endl;
    randEng.seed(seed);
}
void prepareJobs(uint32_t seed) {
    static thread_local std::default_random_engine randEng;
    static thread_local std::once_flag flagInit;
    static thread_local uint64_t jobGen{};
    try {
        std::call_once(flagInit, initJobGen, randEng, seed);
    } catch (std::exception& exp) {
        std::cout << exp.what();
    }
    static thread_local std::uniform_int_distribution<uint32_t> randDis;
    while (jobGen < MAX_JOBS) {
        uint32_t newJobs{randDis(randEng)};
        // std::this_thread::sleep_for(std::chrono::milliseconds(10));
        {
            std::lock_guard<std::mutex> lock(mutexJobsQueue);
            jobsQueue.push(newJobs);
	    ++jobGen;
            // notify the waiting thread (if there is one)
            // any thread in a blocked or waiting state wakes from its slumber  (unblocks it)
            // reacquires the lock on mutex and check the condition again
            jobCondition.notify_one();
        }
    }
    jobCondition.notify_all();
    std::cout << "\n Thread " << std::this_thread::get_id() << " prepared " << jobGen << std::endl;
}

void processJobs() {
	while (totalProcessJobs < MAX_JOBS * std::thread::hardware_concurrency() / 2) {
        	std::unique_lock<std::mutex> lock(mutexJobsQueue);
		std::cout << "\n Total " << totalProcessJobs << std::endl;
        	jobCondition.wait(lock, /* the condition being waited for */ [] { return (totalProcessJobs >= MAX_JOBS * std::thread::hardware_concurrency() / 2 && (jobsQueue.empty()) || !jobsQueue.empty()); });
        	// condition_variable::wait() check the condition
        	// the condition is satisfied => return, still lock the mutex
        	// the condition isn't satisfied => unlock the mutex and put the current thread in a blocked or waiting state
        	// During a call to wait(), the condition variable may check the supplied
        	// contidion any number of times.
        	// It always does so with the mutex locked and will return immediately if the
        	// function provided to test the condition return true
		if (jobsQueue.empty())
		   break;
        	uint32_t processJob{jobsQueue.front()};
		//std::cout << "\n Thread " << std::this_thread::get_id() << "is processing job: " << processJob << std::endl;
        	jobsQueue.pop();
        	lock.unlock();
		++totalProcessJobs;
        	// processing data would be a time-consuming operation
        	// doing something with job
	}
	std::cout << "\nThread " << std::this_thread::get_id() << " done ..." << std::endl;
}

int main() {
    std::vector<uint32_t> threadSeeds(std::thread::hardware_concurrency() / 2);
    auto toDaySeed = randSeed();
    std::cout << "Today seed is : " << toDaySeed << std::endl;
    std::seed_seq seedSeq{toDaySeed};
    seedSeq.generate(std::begin(threadSeeds), std::end(threadSeeds));
    std::copy(std::begin(threadSeeds), std::end(threadSeeds), std::ostream_iterator<uint32_t>(std::cout, " | "));

    std::vector<std::thread> workersPrepareJobs;
    for (auto thrSeed : threadSeeds) {
        workersPrepareJobs.push_back(std::thread(prepareJobs, thrSeed));
    }

    std::vector<std::thread> workersProcessJobs;
    for (int i{}; i < std::thread::hardware_concurrency() / 2; ++i) {
        workersProcessJobs.push_back(std::thread(processJobs));
    }

    for (auto& worker : workersPrepareJobs) {
        worker.join();
    }

    for (auto& worker : workersProcessJobs) {
        worker.join();
    }
    std::cout << "TOTAL PROCESSED JOBS " << totalProcessJobs << std::endl;
    ThreadSafeQueue<uint32_t> safeQueue;
    safeQueue.push(100);
    safeQueue.push(10000);
    std::cout <<"POOPP from safequeue " <<*safeQueue.tryAndPop() << std::endl;
    return 0;
}
