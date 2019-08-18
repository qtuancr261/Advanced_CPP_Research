/*
 * Author: tuantq3
 * File: main.cpp
 *
 * Created on 15/8/2019
 *
 * Testing stl generating random numbers
 */

#include <iostream>
#include <iterator>
#include <random>
#include <vector>

using std::copy;
using std::cout;
using std::endl;
using std::random_device;
using std::seed_seq;
using std::string;
using std::vector;

#define seperatorBeginEnd cout << endl << "-------------------------------------------------------------" << endl

void testObtaningRandomSeeds(int numSeeds) {
    // std::random_device is a uniformly-distributed integer random number generator
    // that produces non-deteministic random numbers
    // Use std::random_device as a seeds generator
    //
    random_device randDev{};
    cout << "Min rand value: " << randDev.min() << endl;
    cout << "Max rand value: " << randDev.max() << endl;
    // the max rand value is equal to std::numeric_limits<unsigned int>::max()
    // if the implementation is using a random number engine and not a non-deteministic source entropy value is equal to 0
    for (int iseed = 0; iseed < numSeeds; ++iseed) {
        cout << "Rand seed: " << randDev() << endl;
    }
    cout << "Entropy " << randDev.entropy() << endl;
    seperatorBeginEnd;
}
void genSeedSequences(seed_seq& initSeedSeq, const string& title, size_t numGenValues = 10) {
    vector<uint> ranVec(numGenValues, 0);
    initSeedSeq.generate(std::begin(ranVec), std::end(ranVec));

    cout << title << endl;
    copy(std::begin(ranVec), std::end(ranVec), std::ostream_iterator<uint>{cout, " - "});
    seperatorBeginEnd;
}
int main(int argc, char* argv[]) {
    // gen single seed value
    testObtaningRandomSeeds(10);
    // gen seed sequences
    seed_seq seedSeq_1;  // default constructor
    genSeedSequences(seedSeq_1, "seedSeq_1 - default constructor ");
    genSeedSequences(seedSeq_1, "seedSeq_1 - default constructor AGAIN");
    genSeedSequences(seedSeq_1, "seedSeq_1 - default constructor AGAIN (different gen num: 5)", 5);
    seed_seq seedSeq_2{2610, 1996, 2018, 12};
    genSeedSequences(seedSeq_2, "seedSeq_2 - consecutive int ");
    genSeedSequences(seedSeq_2, "seedSeq_2 - consecutive int AGAIN");
    genSeedSequences(seedSeq_2, "seedSeq_2 - consecutive int AGAIN (different gen num: 4)", 4);
    genSeedSequences(seedSeq_2, "seedSeq_2 - consecutive int AGAIN");
    genSeedSequences(seedSeq_2, "seedSeq_2 - consecutive int AGAIN (different gen num: 12)", 12);
    random_device rd;
    seed_seq seedSeq_3{rd(), rd()};
    genSeedSequences(seedSeq_3, "seedSeq_3 - use random_device");
    genSeedSequences(seedSeq_3, "seedSeq_3 - use random_device AGAIN (different gen num: 8)", 8);
    genSeedSequences(seedSeq_3, "seedSeq_3 - use random_device AGAIN (different gen num: 16)", 16);
    vector<int> initValue{2610, 1996, 2018, 12};
    seed_seq seedSeq_4(std::begin(initValue), std::end(initValue));
    genSeedSequences(seedSeq_4, "seedSeq_5 - use a range (the same as seedSeq_2)");
    initValue.push_back(2000);
    seed_seq seedSeq_5(std::begin(initValue), std::end(initValue));
    genSeedSequences(seedSeq_5, "seedSeq_5 - use a range ");
    return 0;
}
