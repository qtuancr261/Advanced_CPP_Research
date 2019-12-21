/*
 * Author: tuantq3
 * File: main.cpp
 *
 * Created on 20/12/2019
 */

#include <iostream>
#include <map>
#include <set>
#include <vector>
using std::cout;
using std::endl;
using std::lexicographical_compare;  // same functional with operator <
using std::make_pair;
using std::map;
using std::set;
using std::vector;
int main(int argc, char *argv[]) {
    for (int i{}; i < argc; i++) {
        cout << argv[i] << endl;
    }

    // Let's compare two vector<int> (same type)
    vector<int> vecIA{10, 7, 11, 12, 22};
    vector<int> vecIB{8, 69, 11, 12, 22};
    auto isVecIASmaller = vecIA < vecIB;
    cout << std::boolalpha << isVecIASmaller << endl;
    auto isVecIBBigger = lexicographical_compare(vecIB.begin(), vecIB.end(), vecIA.begin(), vecIA.end());
    cout << std::boolalpha << isVecIBBigger << endl;
    // std::lexicographical_compare does the same thing with operator <

    // Let's compare two different vector to see why it more powerful than operator <
    vector<int> vecIC{22, 10, 23};
    vector<double> vecDD{100.2, 22.5, 33};
    // auto isVecICSmaller = vecIC < vecDD; // you couldn't do that with operator <
    auto isVecICSmaller = lexicographical_compare(vecIC.begin(), vecIC.end(), vecDD.begin(), vecDD.end());
    cout << std::boolalpha << isVecICSmaller << endl;
    vector<uint64_t> vecUIE{300, 543, 29, 4, 1000};
    auto isVecDDBigger = lexicographical_compare(vecUIE.begin(), vecUIE.end(), vecDD.begin(), vecDD.end());
    cout << std::boolalpha << isVecDDBigger << endl;
    return 0;
}
