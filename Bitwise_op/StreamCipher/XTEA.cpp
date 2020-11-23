#include "XTEA.h"

XTEA::XTEA() : _DELTA{0x9E3779B9}, _sum{} {
	// pre calculate all sum
	_sum[0] = 0;
	for (int i{1}; i < 33; ++i) {
		_sum[i] = _sum[i - 1] + _DELTA;
	}
}

bool XTEA::enc(uint32_t rounds, uint32_t data[], const uint32_t key[]) {
	unsigned int i;
	uint32_t v0 = data[0], v1 = data[1];
	for (i = 0; i < rounds; i++) {
		v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (_sum[i] + key[_sum[i] & 1]);
		v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (_sum[i + 1] + key[(_sum[i + 1] >> 11) & 1]);
	}
	data[0] = v0;
	data[1] = v1;
	return true;
}

bool XTEA::dec(uint32_t rounds, uint32_t data[], const uint32_t key[]) {
	unsigned int i;
	uint32_t v0 = data[0], v1 = data[1];
	for (i = 0; i < rounds; i++) {
		v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (_sum[i + 1] + key[(_sum[i + 1] >> 11) & 1]);
		v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (_sum[i] + key[_sum[i] & 1]);
	}
	data[0] = v0;
	data[1] = v1;
	return true;
}
