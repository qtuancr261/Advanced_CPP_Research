#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <random>
#include <thread>
#include <vector>
#include "threadguard.h"
#include "worker.h"
using namespace std;
struct funct {
    int& _refI;
    funct(int& refI) : _refI{refI} {
        // init
    }

    void operator()() const {
        for (int var = 0; var < _refI; ++var) {
            cout << var << " -> " << _refI << endl;
        }
    }

    bool doTheSameThingAsFunctor() {
        for (int var = 0; var < 5; ++var) {
            cout << var << " -> " << 5 << endl;
        }
        return true;
    }
};
int say(string& message) {
    cout << message << endl;
    cout << " ------" << endl;
    message.append(" - said");
    cout << "Internal thread we say after appending: " << message << endl;
    return 1;
}
void processObject(unique_ptr<int> num) {
    // Didn't do anything
    cout << "Thread id " << std::this_thread::get_id() << endl;
}
void sayHi() { cout << "Hi " << endl; }

template <typename Iterator, typename T>
T parallel_calculateSum(Iterator first, Iterator last, T initValue = 0) {
    int length = std::distance(first, last);
    if (length == 0) return initValue;
    const int MIN_ENTRIES_PER_THREAD{32};
    const int MAX_THREADS{(length + MIN_ENTRIES_PER_THREAD) / MIN_ENTRIES_PER_THREAD};
    const int MAX_HW_THREADS{static_cast<int>(thread::hardware_concurrency())};
    int numThreads{(MAX_THREADS < MAX_HW_THREADS ? MAX_THREADS : MAX_HW_THREADS / 2)};
    int entriesPerBlock{length / numThreads};
    std::cout << "Num threads: " << numThreads << "| entries/block: " << entriesPerBlock << std::endl;
    std::vector<T> results(numThreads, 0);
    std::vector<std::thread> threads(numThreads - 1);
    Iterator blockStart{first};
    Worker worker(5);
    for (int i = 0; i < (numThreads - 1); ++i) {
        Iterator blockEnd{blockStart};

        std::advance(blockEnd, entriesPerBlock);
        threads[i] = std::thread(&Worker::calculateSum<Iterator, T>, &worker, blockStart, blockEnd, std::ref(results[i]));
        std::advance(blockStart, entriesPerBlock);
    }
    worker.calculateSum<Iterator, T>(blockStart, last, results[numThreads - 1]);

    for (std::thread& threadI : threads) {
        threadI.join();
    }
    return std::accumulate(std::begin(results), std::end(results), initValue);
}
int main() {
    int i = 20;
    funct F1{i};
    // std::thread works with any callable type
    // pass a function
    thread thread_1{sayHi};
    thread_1.join();

    // so we could pass an instance of a class with a function call operator to the std::thread
    thread thread_2{F1};
    thread_2.join();

    // Or use the functor directly
    thread thread_3{funct(i)};
    thread_3.join();

    //
    thread thread_4{&funct::doTheSameThingAsFunctor, &F1};
    thread_4.join();

    string message{"Hello"};
    // By default the arguments are copied into internal storage
    // Where they can be access by the newly created thread of execution
    // Even if the corresponding parameter in the function is expecting a ref
    // So that you need to wrap the arguments that really need to be ref in std::ref()
    thread thread_5{say, std::ref(message)};
    thread_5.join();
    cout << "outside the thread we say after appending: " << message << endl;

    thread thread_6{Worker(1)};
    thread_6.join();

    // when the source object is a temporary, the move is automatic
    // but when one is a named value, the transfer must be requested directly by calling std::move
    unique_ptr<int> numInt{make_unique<int>(2610)};
    thread thread_7{processObject, move(numInt)};
    thread_7.join();
    // By the way. std::thread have the same ownership semantics as std::unique_ptr
    // They do own a resource: each instance is responsible for managing a thread of execution
    std::random_device randDev;
    std::uniform_int_distribution<int> uniformDistribution{0, 1000};
    std::default_random_engine randEngine{randDev()};
    std::vector<int> randNumbers(12, 0);
    for (int& num : randNumbers) {
        num = uniformDistribution(randEngine);
    }
    std::copy(std::begin(randNumbers), std::end(randNumbers), std::ostream_iterator<int>{std::cout, " - "});
    std::cout << std::endl << "Sum by std::accumulate: " << std::accumulate(std::begin(randNumbers), std::end(randNumbers), 0) << std::endl;
    std::cout << std::endl
              << "Sum by parallel_calculateSum: " << parallel_calculateSum<std::vector<int>::iterator, int>(std::begin(randNumbers), std::end(randNumbers), 0)
              << endl;
    return 0;
}
