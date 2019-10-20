/*
 * Author: tuantq3
 * File: %{Cpp:License:FileName}
 *
 * Created on 17/10/2019
 */
#include <boost/bind.hpp>
#include <boost/coroutine/all.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// Asymmetric corountine
// Corountine pulls data from caller
template <typename T>
using pull_type = typename boost::coroutines::asymmetric_coroutine<T>::pull_type;
// Corountine pushes data to caller
template <typename T>
using push_type = typename boost::coroutines::asymmetric_coroutine<T>::push_type;

// this function teamplate tends to pass the next entry from a vector to the caller it is called
// callee rountine
template <typename T>
void getNextEntry(push_type<T>& sink, const std::vector<T>& vec) {
    for (const auto& entry : vec) {
        sink(entry);
    }
}

// in this example, main() is the caller rountine
int main() {
    // Initialize vector<string>
    std::vector<std::string> vecStr{"2611996", "10111996", "PTIT", "Gamers"};
    // caller rountine must wrap the function in pull_type or push_type depending on whether it intends to pull
    // or push data to it
    // the main function must wrap getNextEntry in an instance of pull_type (our case)
    // boost::bind : 
    // create the instance of pull_tupe invokes the getNextEntry corountine for the first time
    pull_type<std::string> func(boost::bind(getNextEntry<std::string>, ::_1, boost::ref(vecStr)));
    // when the caller run for the first time, we can use it to check if callee has push some data
    while (func) {
        // get the data
        std::cout << func.get() << std::endl;
        // relinquish control to the getNextEntry coroutine
        func();
    }
    return 0;
}
