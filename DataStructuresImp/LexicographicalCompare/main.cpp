/*
 * Author: tuantq3
 * File: main.cpp
 *
 * Created on 20/12/2019
 */

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::lexicographical_compare;
using std::vector;
int main(int argc, char *argv[]) {
    for (int i{}; i < argc; i++) {
        cout << argv[i] << endl;
    }

    vector<int> vecIA{10, 7, 11, 12, 22};
    vector<int> vecIB{8, 69, 11, 12, 22};
    auto isVecIASmaller = vecIA < vecIB;
    cout << std::boolalpha << isVecIASmaller << endl;
    auto isVecIBBigger = lexicographical_compare(vecIB.begin(), vecIB.end(), vecIA.begin(), vecIA.end());
    cout << std::boolalpha << isVecIBBigger << endl;
    return 0;
}
