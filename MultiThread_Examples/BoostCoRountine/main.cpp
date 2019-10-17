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
int main() {
    pull_type<std::string> ge;
    cout << "Hello World!" << endl;
    return 0;
}
