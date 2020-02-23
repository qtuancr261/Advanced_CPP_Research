#ifndef LAZYINITBENCH_H
#define LAZYINITBENCH_H
#include <assert.h>
#include <atomic>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
class LazyInitBench {
private:
    struct Connection {
        std::string host;
        std::atomic<int> countAPI;
        Connection(const std::string& hostName) : host{hostName}, countAPI{0} {}
    };

private:
    std::unique_ptr<Connection> _conn;  // assume this object is shared among many threads and init only once
    std::mutex _connInitMutex;          // case 1: use mutex
    std::once_flag _connInitFlag;

public:
    LazyInitBench();
    void initConnection();
    void doCallAPIWithCheckConnInitMutex();
    void doCallAPIWithStdCallOnceInit();

public: /*bench*/
    static void benchmarkCallAPI(int threadNum, int callAPIPerThread);
};

#endif  // LAZYINITBENCH_H
