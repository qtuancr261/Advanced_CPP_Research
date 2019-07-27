/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: tuantq3
 *
 * Created on June 10, 2019, 4:18 PM
 */

#include <stdint.h>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "tunnelbitwise.h"

#define COUNT_RSBIT(v) ((v)&31)
/*
 * To test over flow with FL_ENTROPY32
 */
#define NFL_ENTROPY64(i) ((1ull + INCR_ENTROPY32(i)) * (1ull + AUTOROT32(i)))
/*
 * To test over flow with DBINC_ENTROPY32
 */
#define DBINC_ENTROPY64(i) INC_ENTROPY32((1ull + (INC_ENTROPY32(i) & 0xffff)) * (1ull + (INC_ENTROPY32(i) >> 16)))
/*
 * To test where POWEROF2 is over flow
 */
#define POWEROF2ULL(n) (1ull << (n))
#define MASK1ULL(nbits) (POWEROF2ULL(nbits) - 1)
const uint64_t MAX32 = MASK1ULL(32);
using namespace std;

void rotateBitset32(bitset<32>& bSet, uint32_t rotateValue) {
	vector<bool> preservedBit;
	preservedBit.reserve(32);
    for (int i = rotateValue - 1; i >= 0; --i) preservedBit.push_back(bSet[i]);
	bSet >>= rotateValue;
    for (int i = 0; i < rotateValue; ++i) bSet.set(31 - i, preservedBit[i]);
}

void autoRotateIsR(uint32_t value) {
	bitset<32> bSet(value);
    uint32_t rotateNBit = COUNT_RSBIT(value);
	rotateBitset32(bSet, rotateNBit);
    assert((bSet.to_ulong() == AUTOROT32(value)) && (bSet == bitset<32>(AUTOROT32(value))));
}

uint32_t getIncr_entropy32(uint32_t value) {
    uint32_t incr_value = INC_ENTROPY32(value);
    uint32_t absDiff = 0;
    return absDiff = (incr_value > value ? incr_value - value : value - incr_value);
}

bool isOverFlow_entropy32(uint32_t value) {
    //	uint64_t nflow_value = NFL_ENTROPY64(value);
    //	uint64_t flow_value = FL_ENTROPY32(value);
    uint64_t nflow_value = DBINC_ENTROPY64(value);
	uint64_t flow_value = DBINC_ENTROPY32(value);
    return (nflow_value > flow_value);
}

template <uint32_t nbits>
void testTSimpleChain() {
	TSimpleNumberChain<nbits> tSNChain;
    tSNChain.init(rand());
	for (uint32_t i = 1; i < tSNChain.capacity(); ++i) {
		tSNChain.next();
		assert(!tSNChain.isEnd());
	}
	// end
	tSNChain.next();
	assert(tSNChain.isEnd());
	cout << "Pass TSimpleNumberChain " << nbits << endl;
}

void testTSimpleNumberChain() {
	testTSimpleChain<3>();
	testTSimpleChain<4>();
	testTSimpleChain<5>();
	testTSimpleChain<6>();
	testTSimpleChain<7>();
	testTSimpleChain<8>();
	testTSimpleChain<9>();
	testTSimpleChain<10>();
	testTSimpleChain<11>();
	testTSimpleChain<12>();
	testTSimpleChain<13>();
	testTSimpleChain<14>();
	testTSimpleChain<15>();
	testTSimpleChain<16>();
	testTSimpleChain<17>();
	testTSimpleChain<18>();
	testTSimpleChain<19>();
	testTSimpleChain<20>();
	testTSimpleChain<21>();
	testTSimpleChain<22>();
	testTSimpleChain<23>();
	testTSimpleChain<24>();
	testTSimpleChain<25>();
	testTSimpleChain<26>();
	testTSimpleChain<27>();
	testTSimpleChain<28>();
	testTSimpleChain<29>();
	testTSimpleChain<30>();
	testTSimpleChain<31>();
    // testTSimpleChain<32>();
}

void testMask1(uint32_t nbits) {
	for (uint32_t i = 1; i <= nbits; ++i) {
        uint64_t mask = MASK1ULL(i);
		uint64_t maskF = MASK1(i);
		cout << mask << " | " << maskF << endl;
		if (mask != maskF) {
			cerr << "POWEROF2(n) overflow at : " << i << endl;
			break;
        }
	}
}
void testOverFlowIncr32() {
    uint64_t stepRange = 50;
    uint64_t stepTest = 1;
    uint32_t countSample = 0;
    uint32_t countFlow = 0;
    uint32_t countIncr2_0 = 0;
    uint32_t countIncr2_8 = 0;
    uint32_t countIncr2_16 = 0;
    uint32_t countIncr2_24 = 0;
    uint32_t last = 0;
    for (uint64_t i = 0; i <= MAX32; i += stepTest) {
        autoRotateIsR(i);
        countFlow += isOverFlow_entropy32(i);
        uint32_t incrValue = getIncr_entropy32(i);
        if (incrValue > (POWEROF2(24)))
            ++countIncr2_24;
        else if (incrValue > (POWEROF2(16)))
            ++countIncr2_16;
        else if (incrValue > (POWEROF2(8)))
            ++countIncr2_8;
        else
            ++countIncr2_0;
        ++countSample;
        stepTest = rand() % stepRange + 1;
        // cout << "Pass " << i << endl;
        // cout << i << "  " <<countSample <<" / MAX SAMPLE" << maxSample << endl;
        last = i;
    }
    cout << "LAst " << last << endl;
    cout << countFlow << "/" << countSample << " ~ " << (double)countFlow / countSample << endl;
    cout << countIncr2_24 << "/" << countSample << " ~ " << (double)countIncr2_24 / countSample << endl;
    cout << countIncr2_16 << "/" << countSample << " ~ " << (double)countIncr2_16 / countSample << endl;
    cout << countIncr2_8 << "/" << countSample << " ~ " << (double)countIncr2_8 / countSample << endl;
    cout << countIncr2_0 << "/" << countSample << " ~ " << (double)countIncr2_8 / countSample << endl;
    // TSimpleMumberChain from
}
int main(int argc, char** argv) {
    srand(974);
    testMask1(64);
    testOverFlowIncr32();
	testTSimpleNumberChain();
	return 0;
}
