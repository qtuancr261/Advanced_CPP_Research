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
    std::clog << "Bench " << Log(LazyInitBench::benchmarkCallAPI) << std::endl;
    std::vector<std::thread> workers;
    LazyInitBench bench;
    for (int i = 0; i < threadNum; ++i) {
        // threads.push_back(std::thread(&LazyInitBench::doCallAPIWithCheckConnInitMutex, &bench));
        // Lambda expression
	// [capture_list] (param_list) mutable -> return_type {body}
	// *capture_list: lists var from the enclosing scope that are to be captured (by value or by ref)
	// *param_list: parameter list to be passed to the lambda when it is called
	// *mutable: optional keyword indicates that copies of vars captured by value can be modified
	// *return_type: optional, when it is ommited the default is the type of the value return, (void - nonthing returned)
	// *body: just like a normal function body
        workers.push_back(std::thread([callAPIPerThread, &bench]() {
            for (int index{}; index < callAPIPerThread; index++) bench.doCallAPIWithCheckConnInitMutex();
        }));
    }
    for (auto& worker : workers) {
        worker.join();
    }
    std::clog << "Result count " << bench._conn->countAPI << std::endl;
}
