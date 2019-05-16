#include "CPUClock.h"
#include "processutil.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "./Bin processID traceTimeInSec";
        return 0;
    }
    int pid = atoi(argv[1]);
    int durationInSec = atoi(argv[2]);

    CpuClock clock;
    int count = 0;
    double total = 0;
    while (clock.elapsedSec() <= durationInSec) {
        double currentCPUUsage = ProcessUtil::GetCpuUsage(pid);
        if (count > 0) total += currentCPUUsage;
        cout << "-> PID: " << pid << "| CPU Usage: " << currentCPUUsage << endl;
        count++;
        sleep(1);
    }
    cout << "Average : " << total / durationInSec << " %" << endl;
    return 0;
}
