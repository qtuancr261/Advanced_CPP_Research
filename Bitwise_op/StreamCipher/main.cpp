/*
 * Author: tuantq3
 * File: %{Cpp:License:FileName}
 *
 * Created on 12/7/2020
 */
#include <iostream>
#include <string>
#include "FeedBackRegister.h"
using namespace std;
int main() {
    FeedBackRegister<uint8_t> _fint{255};
    _fint.printAllState();
    // edBackRegister<float> _float{3.14f};
    // FeedBackRegister<string> _fstring{"rr"};
}
