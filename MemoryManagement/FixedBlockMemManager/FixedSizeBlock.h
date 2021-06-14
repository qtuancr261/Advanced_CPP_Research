/*
 * Author: tuantq3
 * File: FixedSizeBlock.h
 *
 * Created on 19/4/2020
 */
#ifndef FIXEDSIZEBLOCK_H
#define FIXEDSIZEBLOCK_H
#include <cstddef>

template <class Arena>
class FixedBlockMemManager {
public:
	// default constructor
	// char (&a)[N] means: "reference to array (length N) of char"
	template <int N>
	FixedBlockMemManager(char (&a)[N]);
	// copy constructor is prohibited
	FixedBlockMemManager(const FixedBlockMemManager& source) = delete;
	// assignment operator is prohibited (copy version)
	FixedBlockMemManager& operator=(const FixedBlockMemManager& source) = delete;
	// default destructor
	~FixedBlockMemManager() = default;

public:
	void* allocate(size_t);
	void deallocate(void*);
	size_t blockSize() const;
	size_t capacity() const;
	bool isEmpty() const;
	void clear();

private:
	struct freeBlock {
		freeBlock* nextBlock;
	};

	freeBlock* _freeHead;
	size_t _blockSize;
	Arena _arena;
};
#endif  // FIXEDSIZEBLOCK_H
