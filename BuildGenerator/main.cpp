/* For testing only
 * tuantq3 20190504
 *
 *
 *
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "StopWatch.h"
using namespace::std;
const uint8_t IV_Mask[] = {26, 199, 14, 203, 120, 77, 12, 149};
const int IVSize = 8;
void encryptIV(uint8_t* IV, int IVLen) {
    IV[0] = IV[0] ^ IV_Mask[5] ^ IV_Mask[0];
    for (int i = 1; i < IVLen; ++i) {
        IV[i] = IV[i] ^ IV[i - 1] ^ IV_Mask[i];
    }
}

void decryptIV(uint8_t* IV, int IVLen) {
    uint8_t IVTemp[IVLen];
    memcpy(IVTemp, IV, IVLen);
    IV[0] = IVTemp[0] ^ IV_Mask[5] ^ IV_Mask[0];
    for (int i = 1; i < IVLen; ++i) {
        IV[i] = IVTemp[i] ^ IVTemp[i - 1] ^ IV_Mask[i];
    }
}
void outIV(uint8_t* IV, int IVLen) {
    cout << endl;
    for (int i = 0; i < IVLen; ++i) {
        cout << (int)IV[i] << " ";
    }
    cout << endl;
}
int main(int argc, char *argv[])
{
    StopWatch clock;
    uint8_t* IV = new uint8_t[IVSize];
    for (int var = 0; var < IVSize; ++var) {
        IV[var] = rand() % 256;
    }
    outIV(IV, IVSize);
    encryptIV(IV, IVSize);
    outIV(IV, IVSize);
    decryptIV(IV, IVSize);
    outIV(IV, IVSize);
    cout << "Elapsed: " << clock.elapsedSec() << endl;
    return 0;
}
