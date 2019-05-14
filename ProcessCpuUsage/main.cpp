#include <iostream>
#include "processutil.h"
using namespace std;

int main(int argc, char* argv[])
{
    int pid = atoi(argv[1]);
//    while (true) {
//       //std::cout << ProcessUtil::GetCpuUsage()
//    }
    std::cout << " Process " << pid << " " <<  ProcessUtil::GetCpuUsage(pid) <<std::endl;
    return 0;
}
