/*
 * Author: tuantq3
 * File: main.cpp
 *
 * Created on 15/8/2019
 *
 * Testing stl generating random numbers
 */

#include <iostream>
#include <random>
using std::cout;
using std::endl;
using std::random_device;
int main(int argc, char *argv[]) {
    // std::random_device is a uniformly-distributed integer random number generator
    // that produces non-deteministic random numbers
    // Use std::random_device as a seeds generator
    //
    random_device randDev{};
    cout << "Min rand value: " << randDev.min() << endl;
    cout << "Max rand value: " << randDev.max() << endl;
    // the max rand value is equal to std::numeric_limits<unsigned int>::max()
    for (int iseed = 0; iseed < 10; ++iseed) {
        cout << "Rand seed: " << randDev() << endl;
    }
    cout << "Entropy " << randDev.entropy() << endl;
    return 0;
}
