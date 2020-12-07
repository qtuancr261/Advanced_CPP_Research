#ifndef GENERICSTRUCTURES_H
#define GENERICSTRUCTURES_H
#include <cstdint>

struct generic_info_t {
	//
	uint64_t minReadEventID;
	uint64_t currentWriteEventID;
	//
	uint64_t readFileId;
	uint64_t writeFileId;
	//
	uint64_t readOffset;
	uint64_t writeOffset;
};

struct obj_t {
	uint64_t fileFD;
	uint64_t objID;
};

struct file_gen_t {
	obj_t header;
	void* data;
};

#endif	// GENERICSTRUCTURES_H
