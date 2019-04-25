/*
 * Copyright (c) 2012-2019 by Zalo Group.
 * All Rights Reserved.
 */

/* 
 * File:   consumption.h
 * Author: tainp2
 *
 * Created on January 3, 2019, 10:50 AM
 */

#ifndef CONSUMPTION_H
#define CONSUMPTION_H

#include "common/autotest.h"
#include "list32.h"
#include "PocoEx/LoopRunnableAdapter.h"
#include <Poco/Thread.h>
#include "util/proc_util.h"
#include "util/CPUClock.h"
class ConsumptionTest : public AutoTest {
	const static int DEF_NWORKER = 8;
	const static int DEF_NEPOCH = 1000000;
	const static int DEF_NENTRY = 100;

private:
	test::List32 _list32;
	int _nworker;
	int _nepoch;
	int _nentry;
public:

	ConsumptionTest() :
	AutoTest(_T("Consumption test")) {
		Poco::Util::LayeredConfiguration &config = Poco::Util::Application::instance().config();
		_list32.initialize(config);
		ReadOption(config);
	}

	void ReadOption(Poco::Util::LayeredConfiguration &config) {
		_nworker = config.getInt("app.test.consumption.nworker", DEF_NWORKER);
		_nepoch = config.getInt("app.test.consumption.nepoch", DEF_NEPOCH);
		_nentry = config.getInt("app.test.consumption.nentry", DEF_NENTRY);
	}

	static void* testProc(void* param) {
		ConsumptionTest* ctx = (ConsumptionTest*) param;
		test::DataClientPtr cli = ctx->_list32.getDataCli();
		int epoch = ctx->_nepoch;

		TKey key;
		TValue value;
		value.__set_entries(vector<TValueEntry>());
		for (int i = 0; i < ctx->_nentry; ++i) value.entries.push_back(i);
		TValueResult result;
		while (epoch--) {
			key = epoch;
			ctx->_list32.put(cli, key, value, PutPolicy::ADD_OR_UDP);
			//ctx->_list32.get(cli, true, result, key);
		}
		__sync_fetch_and_sub(&ctx->_nworker, 1);
	}

	TestResult Execute() {
		printf("%d workers, nepoch %d\n", _nworker, _nepoch);
		int nthread = _nworker;
		int nreq = _nepoch;
		ProcInfo::Reset();
		CpuClock clock;
		pthread_t* tid = new pthread_t[nthread];

		for (int i = 0; i < nthread; ++i) {
			pthread_create(tid + i, NULL, testProc, this);
		}

//		while (__sync_fetch_and_add(&_nworker, 0)) {
//			sleep(1);
//			printf("cpu usage: %.2lf%%\n", ProcInfo::GetCpuUsage());
//		}
		
		for (int i = 0; i < nthread; ++i) {
			pthread_join(tid[i], NULL);
		}
		uint64_t elapsec = clock.elapsedSec();
		int reqRate = nthread * nreq / elapsec;
		printf("req/s: %d | %d entries \n", reqRate, _nentry);
		return PassedTestResult;
	}

	virtual ~ConsumptionTest() {
	}

};

#endif /* CONSUMPTION_H */

