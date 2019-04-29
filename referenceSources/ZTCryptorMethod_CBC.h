/*
 * Copyright (c) 2012-2018 by Zalo Group.
 * All Rights Reserved.
 */

/* 
 * File:   ZTCryptorMethod_CBC.h
 * Author: tainp2
 *
 * Created on October 27, 2018, 1:05 AM
 */

#ifndef _THRIFT_CRYPTOR_ZTCBCCRYPTOR_H_
#define _THRIFT_CRYPTOR_ZTCBCCRYPTOR_H_

#include <thrift/cryptor/ZTCryptor.h>
#include <thrift/cryptor/ZTCryptorMethod.h>

#include "common.h"

BEG_NSP_CRYPT();

class ZTCryptorMethodCBC : public ZTCryptorMethod {
public:

	ZTCryptorMethodCBC();

	virtual ~ZTCryptorMethodCBC();

	virtual void setup();

	virtual void decrypt(uint8_t*& bytes, uint32_t& size, uint32_t& capacity, AllocationType::type type);

	virtual void encrypt(uint8_t*& bytes, uint32_t& size, uint32_t& capacity, AllocationType::type type);

	virtual void setClientData(const std::xa_string& data);

	virtual void setServerData(const std::xa_string& data);

	virtual int getMetaDataSize() const;

	virtual int getReservedSize() const;

private:
	void getClientKey(uint8_t*& key, uint32_t lkey);
	void getServerKey(uint8_t*& key, uint32_t lkey);

private:
	static void shiftKey(uint8_t* key, uint32_t lkey, int seed);
	static void shiftSessionKey(uint64_t key[]);
	static void decryptIV(uint8_t* plain, uint8_t* cipher, size_t len);
	static void encryptIV(uint8_t* cipher, uint8_t* plain, size_t len);
	static void cbcXorDecrypt(uint64_t* plain, uint64_t* cipher, uint32_t size, uint64_t iv, uint64_t key[]);
	static void cbcXorEncrypt(uint64_t* cipher, uint64_t* plain, uint32_t size, uint64_t iv, uint64_t key[]);
	static void headerXor(uint8_t* dest, uint8_t* src, uint32_t len, uint8_t key);
	static uint8_t getHeaderKey(uint8_t* iv);

private:
	const static int META_DATA_SIZE = 24;
	const static int KEY_SIZE = 32;
	const static int BLOCK_SIZE = 8;
	const static int HEADER_KEY_INDEX = 7;

	uint64_t key_[4];
	uint8_t clientData_[META_DATA_SIZE];
	uint8_t serverData_[META_DATA_SIZE];
	const static uint8_t IV_MASK[BLOCK_SIZE];
	const static uint8_t MASK_UINT8[BLOCK_SIZE];
};

END_NSP_CRYPT();

#endif /* _THRIFT_CRYPTOR_ZTCBCCRYPTOR_H_ */

