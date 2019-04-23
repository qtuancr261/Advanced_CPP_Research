/*
 * Copyright (c) 2012-2019 by Zalo Group.
 * All Rights Reserved.
 */

#include <cstdio>
#include "util/proc_util.h"

int ProcInfo::_procTime;
int ProcInfo::_totalTime;

void ProcInfo::ReadProcStat(int& procTime) {
  char filename[_POSIX_PATH_MAX];
  sprintf(filename, "/proc/%u/stat", (unsigned) getpid());
  FILE* fp = fopen(filename, "r");
  procinfo pinfo;
  fscanf(fp, "%d %s %c %d %d %d %d %d %u %u %u %u %u %d %d",
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

void ProcInfo::ReadCpuStat(int& totalTime) {
  FILE* fp = fopen("/proc/uptime", "r");
  float upTime;
  fscanf(fp, "%f", &upTime);
  fclose(fp);
  totalTime = (int) (upTime * 100);
}

void ProcInfo::Reset() {
  ReadProcStat(_procTime);
  ReadCpuStat(_totalTime);
}

double ProcInfo::GetCpuUsage() {
  int p = _procTime, t = _totalTime;
  Reset();
  return (_procTime - p) * 100.0 / (_totalTime - t);
}
