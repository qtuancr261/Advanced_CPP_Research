#include "keyboardrecorder.h"
KeyboardRecorder::KeyboardRecorder(int &refValue) : refValue{refValue}
{

}

void KeyboardRecorder::operator()() const
{
    {
        for (int i{}; i < refValue; i++)
        {
            string inputString{};
            getline(cin, inputString);
            cout << "You have just typed: " << inputString <<endl;
        }
    }
}
