#include "LazyInitBench.h"
#define Log(msg) #msg
LazyInitBench::LazyInitBench() : _conn{nullptr} {  // nothing here}
}

void LazyInitBench::initConnection() {
    if (!_conn) _conn.reset(new Connection("localhost"));
}

void LazyInitBench::doCallAPIWithCheckConnInitMutex() {
    {
        std::lock_guard<std::mutex> lock(_connInitMutex);
        initConnection();
    }
    _conn->countAPI++;
}

void LazyInitBench::doCallAPIWithStdCallOnceInit() {
    std::call_once(_connInitFlag, &LazyInitBench::initConnection, this);
    _conn->countAPI++;
}

void LazyInitBench::benchmarkCallAPI(int threadNum, int callAPIPerThread) {
    assert(threadNum >= 2 && threadNum <= std::thread::hardware_concurrency());
    assert(callAPIPerThread >= 1000);
    std::clog << "Bench " << Log(LazyInitBench::benchmarkCallAPI) << Log(LazyInitBench::doCallAPIWithCheckConnInitMutex) << std::endl;
    StopWatch _steadyClock{};
    std::vector<std::thread> workers;
    LazyInitBench bench1;
    _steadyClock.restart();
    for (int i{}; i < threadNum; ++i) {
        // threads.push_back(std::thread(&LazyInitBench::doCallAPIWithCheckConnInitMutex, &bench));
        // Lambda expression
        // [capture_list] (param_list) mutable -> return_type {body}
        // *capture_list: lists var from the enclosing scope that are to be captured (by value or by ref)
        // *param_list: parameter list to be passed to the lambda when it is called
        // *mutable: optional keyword indicates that copies of vars captured by value can be modified
        // *return_type: optional, when it is ommited the default is the type of the value return, (void - nonthing returned)
        // *body: just like a normal function body
        workers.push_back(std::thread([callAPIPerThread, &bench1]() {
            for (int index{}; index < callAPIPerThread; ++index) bench1.doCallAPIWithCheckConnInitMutex();
        }));
    }
    for (auto& worker : workers) {
        worker.join();
    }
    std::clog << "Result count " << bench1._conn->countAPI << std::endl;
    std::clog << "Time elapsed: " << _steadyClock.elapsedSec() << " s " << std::endl;
    //-----------------------------------------------------------------------------------------------------------------------------
    workers.clear();
    std::clog << "Bench " << Log(LazyInitBench::benchmarkCallAPI) << Log(LazyInitBench::doCallAPIWithStdCallOnceInit)<<std::endl;
    LazyInitBench bench2;
    _steadyClock.restart();
    for (int i{}; i < threadNum; ++i) {
        workers.push_back(std::thread([callAPIPerThread, &bench2] () {
            for (int index{}; index < callAPIPerThread; ++index) bench2.doCallAPIWithStdCallOnceInit();
        }));
    }
    for (auto& worker : workers) {
        worker.join();
    }
    std::clog << "Result count " << bench2._conn->countAPI << std::endl;
    std::clog << "Time elapsed: " << _steadyClock.elapsedSec() << " s " << std::endl;
}
