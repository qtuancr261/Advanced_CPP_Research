/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "CPUClock.h"

CpuClock::CpuClock() : _startPoint() {}

CpuClock::CpuClock(const CpuClock& srcClock) { _startPoint = srcClock._startPoint; }

CpuClock& CpuClock::operator=(const CpuClock& srcClock) {
	_startPoint = srcClock._startPoint;
	return *this;
}

CpuClock::Timestamp CpuClock::restart() {
	_startPoint = Timestamp();
	return _startPoint;
}

uint64_t CpuClock::elapsedSec() const {
	Timespan elapsed = Timestamp() - _startPoint;
	return elapsed.totalSeconds();
}

uint64_t CpuClock::elapsedMilSec() const {
	Timespan elapsed = Timestamp() - _startPoint;
	return elapsed.totalMilliseconds();
}

uint64_t CpuClock::elapsedMicroSec() const {
	Timespan elapsed = Timestamp() - _startPoint;
	return elapsed.totalMicroseconds();
}

uint64_t CpuClock::elapsedMin() const {
	Timespan elapsed = Timestamp() - _startPoint;
	return elapsed.totalMinutes();
}

uint64_t CpuClock::elapsedHour() const {
	Timespan elapsed = Timestamp() - _startPoint;
	return elapsed.totalHours();
}
