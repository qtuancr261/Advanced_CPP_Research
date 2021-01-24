#include "systime.h"

#include <stdio.h>
#include <iostream>
#include <time.h>
void uninit_xallocator(){
}
JNIEXPORT void Java_jzcommon_corelib_MainApp_setTime
  (JNIEnv *, jobject, jint year, jint month, jint week, jint day) {
		
		struct tm time = { 0 };
		time.tm_year = year - 1900;
		time.tm_mon  = month;
		time.tm_mday = day;
		time.tm_hour = 0;
		time.tm_min  = 0;
		time.tm_sec  = 0;
		if (time.tm_year < 0) time.tm_year = 0;
		time_t t = mktime(&time);
		int ret = -1;
		if (t != (time_t) -1)
				ret = stime(&t);
    std::cout << ret << " " << t << " " << year << " " << month + 1 << " " << week << " " << day  << std::endl;
}
