/*
 * Copyright (c) 2012-2018 by Zalo Group.
 * All Rights Reserved.
 */

/* 
 * File:   ZTCryptorMethod_CBC.cpp
 * Author: tainp2
 *
 * Created on October 27, 2018, 1:05 AM
 */

#include <thrift/cryptor/ZTCryptorMethod_CBC.h>

BEG_NSP_CRYPT();

const uint8_t ZTCryptorMethodCBC::IV_MASK[] = {3, 146, 148, 35, 83, 243, 163, 187};
const uint8_t ZTCryptorMethodCBC::MASK_UINT8[] = {0x0, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f};

ZTCryptorMethodCBC::ZTCryptorMethodCBC()
: ZTCryptorMethod(KEY_SIZE, std::xa_string("CBC_Xor"), Version::CBC_XOR) {
}

ZTCryptorMethodCBC::~ZTCryptorMethodCBC() {
}

void ZTCryptorMethodCBC::setup() {
	uint8_t* k1 = clientData_;
	uint8_t* k2 = serverData_;
	uint8_t* k = (uint8_t*) key_;

	getClientKey(k1, META_DATA_SIZE);
	getServerKey(k2, META_DATA_SIZE);

	for (int i = 0, j = 0; i < keySize_; ++j, i += 2) {
		k[i] = k1[j];
		k[i + 1] = k2[j];
	}
}

void ZTCryptorMethodCBC::shiftKey(uint8_t* key, uint32_t lkey, int seed) {
	if (lkey == 0) return;
	/* TODO: make power of 2 as constant array */
	uint8_t rshift = 1 + (key[seed % lkey] % 7);
	uint8_t lshift = 8 - rshift;
	uint8_t x = key[lkey - 1] & MASK_UINT8[rshift];
	uint8_t y;

	for (int i = 0; i < lkey; ++i) {
		y = key[i] & MASK_UINT8[rshift];
		key[i] = (key[i] >> rshift) | (x << lshift);
		x = y;
	}
}

void ZTCryptorMethodCBC::shiftSessionKey(uint64_t key[]) {
	shiftKey((uint8_t*) & key[0], KEY_SIZE, 2);
}

void ZTCryptorMethodCBC::decryptIV(uint8_t* plain, uint8_t* cipher, size_t len) {
	plain[0] = cipher[0] ^ IV_MASK[5] ^ IV_MASK[0];
	for (int i = 1; i < len; ++i) {
		plain[i] = cipher[i] ^ cipher[i - 1] ^ IV_MASK[i];
	}
}

void ZTCryptorMethodCBC::encryptIV(uint8_t* cipher, uint8_t* plain, size_t len) {
	cipher[0] = plain[0] ^ IV_MASK[5] ^ IV_MASK[0];
	for (int i = 1; i < len; ++i) {
		cipher[i] = plain[i] ^ cipher[i - 1] ^ IV_MASK[i];
	}
}

void ZTCryptorMethodCBC::cbcXorDecrypt(uint64_t* plain, uint64_t* cipher, uint32_t size, uint64_t iv, uint64_t key[]) {
	TTE_THROW_IF(plain + 1 > cipher, "Error during decrypt plain-text at %p, cipher-text at %p", plain, cipher);
	for (int i = 0; i < size; ++i) {
		plain[i] = cipher[i];
	}
	shiftSessionKey(key);
	//
//	TTE_THROW_IF(plain + 1 > cipher, "Error during decrypt plain-text at %p, cipher-text at %p", plain, cipher);
//
//	plain[0] = cipher[0] ^ iv ^ key[0];
//	for (int i = 1, j = 0; i < size; ++i) {
//		j = i & 3 /* % key_length */;
//		plain[i] = cipher[i] ^ cipher[i - 1] ^ key[j];
//	}
//	shiftSessionKey(key);
}

void ZTCryptorMethodCBC::cbcXorEncrypt(uint64_t* cipher, uint64_t* plain, uint32_t size, uint64_t iv, uint64_t key[]) {
	TTE_THROW_IF(plain < cipher, "Error during encrypt plain-text at %p, cipher-text at %p", plain, cipher);
	for (int i = 0; i < size; ++i) {
		cipher[i] = plain[i];
	}
	shiftSessionKey(key);
	//
//	TTE_THROW_IF(plain < cipher, "Error during encrypt plain-text at %p, cipher-text at %p", plain, cipher);
//	uint64_t prevCipher = cipher[0] = plain[0] ^ iv ^ key[0];
//	for (int i = 1; i < size; ++i) {
//		prevCipher = cipher[i] = plain[i] ^ prevCipher ^ key[i & 3];
//	}
//	shiftSessionKey(key);
	//
//	TTE_THROW_IF(plain < cipher, "Error during encrypt plain-text at %p, cipher-text at %p", plain, cipher);
//	cipher[0] = plain[0] ^ iv ^ key[0];
//	for (int i = 1, j = 0; i < size; ++i) {
//		j = i & 3 /* % key_length */;
//		cipher[i] = plain[i] ^ cipher[i - 1] ^ key[j];
//	}
//	shiftSessionKey(key);
}

void ZTCryptorMethodCBC::headerXor(uint8_t* dest, uint8_t* src, uint32_t len, uint8_t key) {
	if (dest < src) {
		for (int i = 0; i < len; ++i) {
			dest[i] = src[i] ^ key;
		}
	} else {
		for (int i = len - 1; i >= 0; --i) {
			dest[i] = src[i] ^ key;
		}
	}
}

uint8_t ZTCryptorMethodCBC::getHeaderKey(uint8_t* iv) {
	return (iv[HEADER_KEY_INDEX] == 0 || iv[HEADER_KEY_INDEX] == 32)
			? iv[HEADER_KEY_INDEX] + 3 : iv[HEADER_KEY_INDEX];
}

void ZTCryptorMethodCBC::decrypt(uint8_t*& bytes, uint32_t& size, uint32_t& capacity, AllocationType::type type) {
	TTE_THROW_IF(size > capacity, "Overflow len %d vs %u", size, capacity);

	uint8_t* plain = bytes, *cipher = bytes;
	int32_t remain = size;

	TTE_THROW_IF((remain -= PROTVER_BYTES) < 0, "Protocol version: No more data to read");
	TTE_THROW_IF(cipher[0] != encryptVersion_, "Wrong encrypt version %d", cipher[0]);
	cipher += PROTVER_BYTES;

	/* Read Thrift magic */
	TTE_THROW_IF((remain -= MAGIC_BYTES) < 0, "ThriftMagicField: No more data to read");
	*(uint32_t*) plain = *(uint32_t*) cipher;
	plain += MAGIC_BYTES;
	cipher += MAGIC_BYTES;

	uint8_t iv[ZTCryptorMethodCBC::BLOCK_SIZE];
	const uint8_t blockSize = ZTCryptorMethodCBC::BLOCK_SIZE;

	/* Read IV field */
	TTE_THROW_IF((remain -= blockSize) < 0, "Iv: No more data to read");
	uint8_t hkey = getHeaderKey(cipher);
	decryptIV(iv, cipher, blockSize);
	cipher += blockSize;

	/* Read function length */
	TTE_THROW_IF((remain -= FUNCLEN_BYTES) < 0, "FunctionLength: No more data to read");
	headerXor(plain, cipher, FUNCLEN_BYTES, hkey);
	int32_t funcLen = ntohl(*(uint32_t*) plain);
	TTE_THROW_IF(funcLen < 0, "Function length negative");
	plain += FUNCLEN_BYTES;
	cipher += FUNCLEN_BYTES;

	/* Read function name & sequence id */
	TTE_THROW_IF((remain -= funcLen) < 0, "FunctionName: No more data to read, need %d", funcLen);
	TTE_THROW_IF((remain -= SEQID_BYTES) < 0, "SequenceId: No more data to read");
	funcLen += SEQID_BYTES; /* add sequence id */
	headerXor(plain, cipher, funcLen, hkey);
	plain += funcLen;
	cipher += funcLen;

	TTE_THROW_IF(remain % blockSize, "Thrift encrypted data length must be a multiple of block size");
	cbcXorDecrypt((uint64_t*) plain
			, (uint64_t*) cipher
			, remain / blockSize /* just size of data */
			, *(uint64_t*) iv
			, key_);

	plain += remain;
	size = plain - bytes;

	/* de-padding */
	int8_t blockSizeRemain = blockSize;
	while (--blockSizeRemain && size > 0 && bytes[size - 1] != 0) --size;
}

void ZTCryptorMethodCBC::encrypt(uint8_t*& bytes, uint32_t& size, uint32_t& capacity, AllocationType::type type) {
	const uint8_t blockSize = ZTCryptorMethodCBC::BLOCK_SIZE;
	const size_t reserved = getReservedSize();

	uint32_t funcLen = ntohl(*(uint32_t*) (bytes + reserved + FRAMESIZE_BYTES + MAGIC_BYTES));
	uint32_t hsize = FUNCLEN_BYTES + funcLen + SEQID_BYTES; /* funcLen | funcName | seqID */
	uint32_t dsize = size - (FRAMESIZE_BYTES + MAGIC_BYTES + reserved) - hsize;
	uint32_t padLen = blockSize - 1 - ((dsize - 1) % blockSize);
	uint32_t snew = FRAMESIZE_BYTES + PROTVER_BYTES + MAGIC_BYTES + blockSize + hsize + dsize + padLen;

	uint8_t iv[ZTCryptorMethodCBC::BLOCK_SIZE];
	uint8_t headerKey;
	GenerateRandom(iv, blockSize);

	if (snew > capacity) {
		capacity = snew;
		Reallocate(bytes, size, capacity, type);
	}
	size = snew;

	uint8_t* plain, *cipher;
	plain = bytes + reserved + FRAMESIZE_BYTES;
	cipher = bytes + FRAMESIZE_BYTES;

	/* add encyptVersion */
	*(uint8_t*) cipher = (uint8_t) encryptVersion_;
	cipher += PROTVER_BYTES;

	/* add magic field*/
	*(uint32_t*) cipher = *(uint32_t*) plain;
	cipher += MAGIC_BYTES;
	plain += MAGIC_BYTES;

	/* add iv field */
	encryptIV(cipher, iv, blockSize);
	headerKey = getHeaderKey(cipher);
	cipher += blockSize;

	headerXor(cipher, plain, hsize, headerKey);
	cipher += hsize;
	plain += hsize;

	GenerateRandom(plain + dsize, padLen);
	for (int i = 0; i < padLen; ++i) plain[dsize + i] |= 0x2;
	dsize += padLen;

	TTE_THROW_IF(dsize % blockSize, "Thrift encrypted data length must be a multiple of block size");
	cbcXorEncrypt((uint64_t*) cipher
			, (uint64_t*) plain
			, dsize / blockSize
			, *(uint64_t*) iv
			, key_);
}

void ZTCryptorMethodCBC::setClientData(const std::xa_string& data) {
	TTE_THROW_IF(data.size() != META_DATA_SIZE, "Invalid meta data from client.");
	memcpy(clientData_, data.data(), data.size());
}

void ZTCryptorMethodCBC::setServerData(const std::xa_string& data) {
	TTE_THROW_IF(data.size() != META_DATA_SIZE, "Invalid meta data from server.");
	memcpy(serverData_, data.data(), data.size());
}

int ZTCryptorMethodCBC::getMetaDataSize() const {
	return META_DATA_SIZE;
}

int ZTCryptorMethodCBC::getReservedSize() const {
	return PROTVER_BYTES + BLOCK_SIZE;
}

void ZTCryptorMethodCBC::getClientKey(uint8_t*& key, uint32_t lkey) {
	shiftKey(key, lkey, 0);
	key += 4;
}

void ZTCryptorMethodCBC::getServerKey(uint8_t*& key, uint32_t lkey) {
	shiftKey(key, lkey, 1);
	key += 4;
}

END_NSP_CRYPT();