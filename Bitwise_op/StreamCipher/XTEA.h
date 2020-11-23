#ifndef XTEA_H
#define XTEA_H
#include <cstdint>

class XTEA {
	// ref: https://en.wikipedia.org/wiki/XTEA
	// benchmark test with 64-bit key
private:
	const uint32_t _DELTA;
	uint32_t _sum[33];

public:
	XTEA();
	~XTEA() = default;

	bool enc(uint32_t rounds, uint32_t data[2], uint32_t const key[2]);
	bool dec(uint32_t rounds, uint32_t data[2], uint32_t const key[2]);
};

#endif	// XTEA_H
