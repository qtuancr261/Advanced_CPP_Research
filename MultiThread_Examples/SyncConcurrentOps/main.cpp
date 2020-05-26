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
std::mutex mutexJobsQueue;

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
        // std::cout << "JobID: " << newJobs << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        {
            std::lock_guard<std::mutex> lock(mutexJobsQueue);
            jobsQueue.push(newJobs);
            // notify the waiting thread (if there is one)
            // any thread in a blocked or waiting state wakes from its slumber  (unblocks it)
            // reacquires the lock on mutex and check the condition again
            jobCondition.notify_one();
        }
    }
}

void processJobs() {
	while (true) {
        std::unique_lock<std::mutex> lock(mutexJobsQueue);
        jobCondition.wait(lock, /* the condition being waited for */ [] { return !jobsQueue.empty(); });
        // condition_variable::wait() check the condition
        // the condition is satisfied => return, still lock the mutex
        // the condition isn't satisfied => unlock the mutex and put the current thread in a blocked or waiting state
        //
        uint32_t processJob{jobsQueue.front()};
        jobsQueue.pop();
        lock.unlock();
        // processing data would be a time-consuming operation
        // doing something with job
        std::cout << "\n Thread " << std::this_thread::get_id() << "is processing job: " << processJob << std::endl;
	}
}

int main() {
    std::vector<uint32_t> threadSeeds(std::thread::hardware_concurrency());
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
    for (int i{}; i < 2; ++i) {
        workersProcessJobs.push_back(std::thread(processJobs));
    }

    for (auto& worker : workersPrepareJobs) {
        worker.join();
    }

    for (auto& worker : workersProcessJobs) {
        worker.join();
    }

    return 0;
}
