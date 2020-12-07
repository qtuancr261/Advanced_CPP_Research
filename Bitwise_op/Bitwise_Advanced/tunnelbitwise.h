/*
 *
 * Created on June 6, 2019, 3:26 PM
 */

#ifndef ZACOMMTUNNEL2_H
#define ZACOMMTUNNEL2_H

#include <assert.h>
#include <cstdint>
#define RSHIFT8(i, s) (((i) >> ((s)&7)) | ((i) << (8 - ((s)&7))))

#define RSHIFT32(i, s) (((i) >> ((s)&31)) | ((i) << (32 - ((s)&31))))

#define AUTOROT32(i) RSHIFT32((i), (i))

#define INC_ENTROPY8(i) ((i) ^ RSHIFT8((i), 2) ^ RSHIFT8((i), 4))

#define INC_ENTROPY32(i) ((i) ^ RSHIFT32((i), 8) ^ RSHIFT32((i), 16))

#define DBINC_ENTROPY32(i) INC_ENTROPY32((1 + (INC_ENTROPY32(i) & 0xffff)) * (1 + (INC_ENTROPY32(i) >> 16)))

#define POWEROF2(n) (1 << (n))

#define MASK1(nbits) (POWEROF2(nbits) - 1)

template <uint32_t NBITS>
class TSimpleNumberChain {
private:
	uint32_t value0;
	uint32_t value;
	uint32_t step;

public:
    TSimpleNumberChain() {}

    TSimpleNumberChain(uint32_t seed) { init(seed); }

    uint32_t capacity() const { return POWEROF2(NBITS); }

	/**
	 * @param seed: dùng 2*NBITS-2 bits thấp của seed
	 * {NBITS-2 bits: step}{NBITS lowest bits: value0}
	 */
	void init(uint32_t seed) {
		assert(NBITS > 2);
		value0 = seed & MASK1(NBITS);
		step = ((RSHIFT32(seed, NBITS) & MASK1(NBITS - 2)) << 1) + POWEROF2(NBITS - 2) + 1;
		value = value0;
	}

	/**
	 * @return số ngẫu nhiên NBITS
	 */
	uint32_t next() {
		value = (value + step) & MASK1(NBITS);
		return value;
	}

    bool isEnd() const { return value == value0; }
};

/**
 * dung lượng bộ sinh: 2^(3*NBITS-2)
 *
 */

#endif /* ZACOMMTUNNEL2_H */
