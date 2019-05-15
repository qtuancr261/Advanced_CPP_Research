#include "processutil.h"

int ProcessUtil::_procTime = 0;
int ProcessUtil::_totalTime = 0;

void ProcessUtil::ReadProcStat(int& procTime, int pid) {
    char filename[_POSIX_PATH_MAX];
    sprintf(filename, "/proc/%u/stat", static_cast<unsigned>(pid));
    FILE* fp = fopen(filename, "r");
    procinfo pinfo;
    fscanf(fp,
           "%d %s %c %d %d %d %d %d %u %u %u %u %u %d %d",
           &(pinfo.pid),
           pinfo.exName,
           &(pinfo.state),
           &(pinfo.ppid),
           &(pinfo.pgrp),
           &(pinfo.session),
           &(pinfo.tty),
           &(pinfo.tpgid),
           &(pinfo.flags),
           &(pinfo.minflt),
           &(pinfo.cminflt),
           &(pinfo.majflt),
           &(pinfo.cmajflt),
           &(pinfo.utime),
           &(pinfo.stime));
    fclose(fp);
    procTime = pinfo.utime + pinfo.stime;
}
void ProcessUtil::ReadCpuStat(int& totalTime) {
    FILE* fp = fopen("/proc/uptime", "r");
    float upTime;
    fscanf(fp, "%f", &upTime);
    fclose(fp);
    totalTime = static_cast<int>(upTime * 100);
}

void ProcessUtil::Reset(int pid) {
    ReadProcStat(_procTime, pid);
    ReadCpuStat(_totalTime);
}

double ProcessUtil::GetCpuUsage(int pid) {
    int p = _procTime, t = _totalTime;
    Reset(pid);
    return (_procTime - p) * 100.0 / (_totalTime - t);
}
