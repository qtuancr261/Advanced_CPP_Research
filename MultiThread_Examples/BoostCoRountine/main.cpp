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
template <typename T>
using pull_type = typename boost::coroutines::asymmetric_coroutine<T>::pull_type;
//
template <typename T>
using push_type = typename boost::coroutines::asymmetric_coroutine<T>::push_type;

template <typename T>
void getNextEntry(push_type<T>& sink, const std::vector<T>& vec) {
    std::cout << "Start \n";
    for (const auto& entry : vec) {
        std::cout << "Resume \n";
        sink(entry);
        std::cout << "Suspend \n";
    }
}

int main() {
    std::vector<std::string> vecStr{"2611996", "10111996", "PTIT", "Gamers"};
    pull_type<std::string> func(boost::bind(getNextEntry<std::string>, ::_1, boost::ref(vecStr)));
    while (func) {
        std::cout << func.get() << std::endl;
        func();
    }
    return 0;
}
