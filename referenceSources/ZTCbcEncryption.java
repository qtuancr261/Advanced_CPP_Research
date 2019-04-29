/*
 * Copyright (c) 2012-2019 by Zalo Group.
 * All Rights Reserved.
 */
package com.vng.zing.thrift.encrypt;

/**
 * @input input = thrift version + functionLen + funcionName + sequenceId +
 * plainData.
 * @output output = encrypt version (protocol version) + thrift version + iv +
 * encryptedFunctionLen + encryptedFunctionName + encryptedSequenceId +
 * encryptedData
 * @author hienpt3
 */
public class ZTCbcEncryption extends ZTEncryptionMethod {

	private static class EncryptHeaderResult {

		public int iterInput;
		public int iterOutput;
		public byte[] iv;

		public EncryptHeaderResult(int iterInput, int iterOutput, byte[] iv) {
			this.iterInput = iterInput;
			this.iterOutput = iterOutput;
			this.iv = iv;
		}
	}

	private static final int SEQ_ID_SIZE = 4;
	private static final int FUNC_NAME_LEN_SIZE = 4;
	private static final byte ENCRYPT_VERSION = 1;
	private static final int THRIFT_VERSION_SIZE = 4;
	private static final int FUNC_NAME_SIZE_LEN = 4;
	private static final int KEY_INDEX_IN_IV = 7;
	private final int maxAddedSize = getIVLen() + getBlockLen()/*padding*/ + ENCRYPT_VERSION_SIZE;

	@Override
	public ZTEncryptionMethod.EncryptResult encrypt(byte[] input, int offset, int length, byte[] key) {
		verifyInputData(input, offset, length, key);
		if (length == 0) {
			return new ZTEncryptionMethod.EncryptResult(input, offset, length);
		}
		final byte[] output = new byte[length + maxAddedSize];
		final EncryptHeaderResult res = encryptHeader(input, offset, length, output, 0);
		res.iterOutput = encryptBuf(input, res.iterInput, length - res.iterInput,
				key, res.iv, output, res.iterOutput);
		return new ZTEncryptionMethod.EncryptResult(output, 0, res.iterOutput);
	}

	private void verifyInputData(byte[] input, int offset, int length, byte[] key) throws RuntimeException {
		if (offset < 0) {
			throw new RuntimeException("Underflow offset " + offset);
		}
		if (offset >= input.length) {
			throw new RuntimeException("Overflow offset " + offset + " vs " + input.length);
		}
		if (length < 0) {
			throw new RuntimeException("Underflow len " + length);
		}
		if (length > input.length) {
			throw new RuntimeException("Overflow len " + length + " vs " + input.length);
		}
		if (offset + length > input.length) {
			throw new RuntimeException("Invalid data range offset " + offset + " len " + length + " cap " + input.length);
		}
		if (key.length != getKeyLen()) {
			throw new RuntimeException("Wrong key len " + key.length);
		}
	}

	private EncryptHeaderResult encryptHeader(byte[] input, int iterInput, int length, byte[] output, int iterOutput) {
		return encryptHeader(input, iterInput, length, output, iterOutput, null);
	}

	private EncryptHeaderResult encryptHeader(byte[] input, int iterInput, int length, byte[] output, int iterOutput, byte[] ivParameter) {
		output[iterOutput++] = ENCRYPT_VERSION;
		int remainingLen = length - iterInput;
		if (remainingLen < THRIFT_VERSION_SIZE) {
			throw new RuntimeException("Not enough len for thrift version " + remainingLen + " vs " + THRIFT_VERSION_SIZE);
		}
		System.arraycopy(input, iterInput, output, iterOutput, THRIFT_VERSION_SIZE);
		iterInput += THRIFT_VERSION_SIZE;
		iterOutput += THRIFT_VERSION_SIZE;
		//
		final int ivLen = getIVLen();
		final byte[] iv = (ivParameter != null && ivParameter.length == ivLen) ? ivParameter : ZTEncryptionUtil.generateRandomData(ivLen);
		final byte[] encryptedIV = xorEncryptIV(iv);
		System.arraycopy(encryptedIV, 0, output, iterOutput, ivLen);
		iterOutput += ivLen;
		//
		remainingLen = length - iterInput;
		if (remainingLen < FUNC_NAME_SIZE_LEN) {
			throw new RuntimeException("Not enough len for func name size " + remainingLen + " vs " + FUNC_NAME_SIZE_LEN);
		}
		final int funcNameLen = getInt(input, iterInput);
		//
		final int headerFuncLen = FUNC_NAME_LEN_SIZE + funcNameLen + SEQ_ID_SIZE;
		remainingLen = length - iterInput;
		if (remainingLen < headerFuncLen) {
			throw new RuntimeException("Not enough len for header func " + remainingLen + " vs " + headerFuncLen);
		}
		final byte encryptingByte = (encryptedIV[KEY_INDEX_IN_IV] == 0 || encryptedIV[KEY_INDEX_IN_IV] == 32)
				? (byte) (encryptedIV[KEY_INDEX_IN_IV] + 3) : encryptedIV[KEY_INDEX_IN_IV];
		for (int i = 0; i < headerFuncLen; i++) {
			output[iterOutput++] = (byte) (input[iterInput++] ^ encryptingByte);
		}
		return new EncryptHeaderResult(iterInput, iterOutput, iv);
	}

	private int encryptBuf(byte[] input, int offset, int length, byte[] key, byte[] iv, byte[] output, int iterOutput) {
		return encryptBuf(input, offset, length, key, iv, output, iterOutput, null);
	}
//
//	private int encryptBuf(byte[] input, int offset, int length, byte[] key, byte[] iv, byte[] output, int iterOutput, byte[] pad) {
//		if (length < 1/*at least one ending zero byte*/) {
//			throw new RuntimeException("Not enough len for last zero byte " + length + " vs 1");
//		}
//		final int blockLen = getBlockLen();
//		final int paddingSize = getPaddingSize(length, blockLen);
//		final int lenAfterPadding = length + paddingSize;
//		final int lastBlockDataLen = blockLen - paddingSize;
//		byte[] inputLastBlock = null;
//		if (pad != null) {
//			if (pad.length != blockLen) {
//				throw new RuntimeException("Padding size not equals one block len " + pad.length);
//			}
//			inputLastBlock = pad;
//            System.arraycopy(input, offset + length - lastBlockDataLen, inputLastBlock, 0, lastBlockDataLen);
//		} else if (paddingSize > 0) {
//			inputLastBlock = generatePadding(blockLen);
//            System.arraycopy(input, offset + length - lastBlockDataLen, inputLastBlock, 0, lastBlockDataLen);
//		}
//		//
//		int kpos = 0, pos = iterOutput;
//		int it = offset;
//		if (length < blockLen) {
//			input = inputLastBlock;
//			it = 0;
//		}
//		byte prevOutput0 = output[pos++] = (byte) (input[it++] ^ iv[0] ^ key[kpos + 0]);
//		byte prevOutput1 = output[pos++] = (byte) (input[it++] ^ iv[1] ^ key[kpos + 1]);
//		byte prevOutput2 = output[pos++] = (byte) (input[it++] ^ iv[2] ^ key[kpos + 2]);
//		byte prevOutput3 = output[pos++] = (byte) (input[it++] ^ iv[3] ^ key[kpos + 3]);
//		byte prevOutput4 = output[pos++] = (byte) (input[it++] ^ iv[4] ^ key[kpos + 4]);
//		byte prevOutput5 = output[pos++] = (byte) (input[it++] ^ iv[5] ^ key[kpos + 5]);
//		byte prevOutput6 = output[pos++] = (byte) (input[it++] ^ iv[6] ^ key[kpos + 6]);
//		byte prevOutput7 = output[pos++] = (byte) (input[it++] ^ iv[7] ^ key[kpos + 7]);
//		//
//		final int nBlock = lenAfterPadding / blockLen;
//		final int ilastBlock = nBlock - 1;
//		final int keyLen = getKeyLen();
//		for (int iblock = 1; iblock < nBlock; iblock++) {
//			kpos += blockLen;
//			if (kpos == keyLen) {
//				kpos = 0;
//			}
//			if (iblock == ilastBlock && inputLastBlock != null) {
//				input = inputLastBlock;
//				it = 0;
//			}
//			prevOutput0 = output[pos++] = (byte) (input[it++] ^ prevOutput0 ^ key[kpos + 0]);
//			prevOutput1 = output[pos++] = (byte) (input[it++] ^ prevOutput1 ^ key[kpos + 1]);
//			prevOutput2 = output[pos++] = (byte) (input[it++] ^ prevOutput2 ^ key[kpos + 2]);
//			prevOutput3 = output[pos++] = (byte) (input[it++] ^ prevOutput3 ^ key[kpos + 3]);
//			prevOutput4 = output[pos++] = (byte) (input[it++] ^ prevOutput4 ^ key[kpos + 4]);
//			prevOutput5 = output[pos++] = (byte) (input[it++] ^ prevOutput5 ^ key[kpos + 5]);
//			prevOutput6 = output[pos++] = (byte) (input[it++] ^ prevOutput6 ^ key[kpos + 6]);
//			prevOutput7 = output[pos++] = (byte) (input[it++] ^ prevOutput7 ^ key[kpos + 7]);
//		}
//		shiftSessionKey(key, 0, keyLen);
//		return pos;
//	}

	private int encryptBuf(byte[] input, int offset, int length, byte[] key, byte[] iv, byte[] output, int iterOutput, byte[] pad) {
		if (length < 1/*at least one ending zero byte*/) {
			throw new RuntimeException("Not enough len for last zero byte " + length + " vs 1");
		}
		final int blockLen = getBlockLen();
		final int paddingSize = getPaddingSize(length, blockLen);
		final int lenAfterPadding = length + paddingSize;
		final int lastBlockDataLen = blockLen - paddingSize;
		byte[] inputLastBlock = null;
		if (pad != null) {
			if (pad.length != blockLen) {
				throw new RuntimeException("Padding size not equals one block len " + pad.length);
			}
			inputLastBlock = pad;
            System.arraycopy(input, offset + length - lastBlockDataLen, inputLastBlock, 0, lastBlockDataLen);
		} else if (paddingSize > 0) {
			inputLastBlock = generatePadding(blockLen);
            System.arraycopy(input, offset + length - lastBlockDataLen, inputLastBlock, 0, lastBlockDataLen);
		}
		//
		int kpos = 0, pos = iterOutput;
		int it = offset;
		if (length < blockLen) {
			input = inputLastBlock;
			it = 0;
		}
		//
		final int nBlock = lenAfterPadding / blockLen;
		final int keyLen = getKeyLen();
		for (int iblock = 0; iblock < nBlock; iblock++) {
			output[pos++] = input[it++];
			output[pos++] = input[it++];
			output[pos++] = input[it++];
			output[pos++] = input[it++];
			output[pos++] = input[it++];
			output[pos++] = input[it++];
			output[pos++] = input[it++];
			output[pos++] = input[it++];
		}
		shiftSessionKey(key, 0, keyLen);
		return pos;
	}

	private int getPaddingSize(int len, int blockLen) {
		return blockLen - 1 - (len + blockLen - 1) % blockLen;
	}

	@Override
	protected byte[] generatePadding(int length) {
		return ZTEncryptionUtil.generateNoneZeroBytes(length);
	}

	@Override
	public ZTEncryptionMethod.EncryptResult decrypt(byte[] input, int offset, int length, byte[] key) {
		verifyInputData(input, offset, length, key);
		if (length == 0) {
			return new ZTEncryptionMethod.EncryptResult(input, offset, length);
		}
		final byte[] output = new byte[input.length - getIVLen() - ENCRYPT_VERSION_SIZE];
		final EncryptHeaderResult res = decryptHeader(input, offset, length, output, 0);
		res.iterOutput = decryptBuf(input, res.iterInput, length - res.iterInput, key, res.iv, output, res.iterOutput);
		return new ZTEncryptionMethod.EncryptResult(output, 0, res.iterOutput);
	}

	private EncryptHeaderResult decryptHeader(byte[] input, int iterInput, int length, byte[] output, int iterOutput) {
		int remainingLen = length - iterInput;
		if (remainingLen < ENCRYPT_VERSION_SIZE) {
			throw new RuntimeException("Not enough len for thrift version " + remainingLen + " vs " + ENCRYPT_VERSION_SIZE);
		}
		if (ENCRYPT_VERSION != input[iterInput]) {
			throw new RuntimeException("Wrong encrypt version " + input[iterInput] + " vs " + ENCRYPT_VERSION);
		}
		++iterInput;
		//
		remainingLen = length - iterInput;
		if (remainingLen < THRIFT_VERSION_SIZE) {
			throw new RuntimeException("Not enough len for thrift version " + remainingLen + " vs " + THRIFT_VERSION_SIZE);
		}
		for (int cnt = 0; cnt < THRIFT_VERSION_SIZE; cnt++) {
			output[iterOutput++] = input[iterInput++];
		}
		//
		remainingLen = length - iterInput;
		if (remainingLen < getIVLen()) {
			throw new RuntimeException("Not enough len for IV len " + remainingLen + " vs " + getIVLen());
		}
		final byte[] iv = new byte[getIVLen()];
		for (int cnt = 0; cnt < getIVLen(); cnt++) {
			iv[cnt] = input[iterInput++];
		}
		final byte[] decryptedIV = xorDecryptIV(iv);
		//
		remainingLen = length - iterInput;
		if (remainingLen < FUNC_NAME_SIZE_LEN) {
			throw new RuntimeException("Not enough len for func name size " + remainingLen + " vs " + FUNC_NAME_SIZE_LEN);
		}
		final byte decryptingByte = (iv[KEY_INDEX_IN_IV] == 0 || iv[KEY_INDEX_IN_IV] == 32)
				? (byte) (iv[KEY_INDEX_IN_IV] + 3) : iv[KEY_INDEX_IN_IV];
		for (int cnt = 0; cnt < FUNC_NAME_SIZE_LEN; cnt++) {
			output[iterOutput++] = (byte) (input[iterInput++] ^ decryptingByte);
		}
		final int funcNameLen = getInt(output, iterOutput - FUNC_NAME_SIZE_LEN);
		//
		final int headerFuncLen = funcNameLen + SEQ_ID_SIZE; // function len field already decrypted
		remainingLen = length - iterInput;
		if (remainingLen < headerFuncLen) {
			throw new RuntimeException("Not enough len for header func " + remainingLen + " vs " + headerFuncLen);
		}
		for (int cnt = 0; cnt < headerFuncLen; cnt++) {
			output[iterOutput++] = (byte) (input[iterInput++] ^ decryptingByte);
		}
		return new EncryptHeaderResult(iterInput, iterOutput, decryptedIV);
	}
//
//	private int decryptBuf(byte[] input, int offset, int length, byte[] key, byte[] iv, byte[] output, int iterOutput) {
//		final int blockLen = getBlockLen();
//		if (length < blockLen) {
//			throw new RuntimeException("Not enough len for at least one block " + length + " vs " + blockLen);
//		}
//		if (length % blockLen != 0) {
//			throw new RuntimeException("Wrong encrypted data len not fit with blockLen " + length + " vs " + blockLen);
//		}
//		//
//		int kpos = 0, iterInput = offset;
//		output[iterOutput++] = (byte) (iv[0] ^ input[iterInput++] ^ key[kpos + 0]);
//		output[iterOutput++] = (byte) (iv[1] ^ input[iterInput++] ^ key[kpos + 1]);
//		output[iterOutput++] = (byte) (iv[2] ^ input[iterInput++] ^ key[kpos + 2]);
//		output[iterOutput++] = (byte) (iv[3] ^ input[iterInput++] ^ key[kpos + 3]);
//		output[iterOutput++] = (byte) (iv[4] ^ input[iterInput++] ^ key[kpos + 4]);
//		output[iterOutput++] = (byte) (iv[5] ^ input[iterInput++] ^ key[kpos + 5]);
//		output[iterOutput++] = (byte) (iv[6] ^ input[iterInput++] ^ key[kpos + 6]);
//		output[iterOutput++] = (byte) (iv[7] ^ input[iterInput++] ^ key[kpos + 7]);
//		//
//		final int nBlock = length / blockLen;
//		final int keyLen = getKeyLen();
//		int prevIterInput = iterInput - blockLen;
//		for (int iblock = 1; iblock < nBlock; iblock++) {
//			kpos += blockLen;
//			if (kpos == keyLen) {
//				kpos = 0;
//			}
//			output[iterOutput++] = (byte) (input[prevIterInput++] ^ input[iterInput++] ^ key[kpos + 0]);
//			output[iterOutput++] = (byte) (input[prevIterInput++] ^ input[iterInput++] ^ key[kpos + 1]);
//			output[iterOutput++] = (byte) (input[prevIterInput++] ^ input[iterInput++] ^ key[kpos + 2]);
//			output[iterOutput++] = (byte) (input[prevIterInput++] ^ input[iterInput++] ^ key[kpos + 3]);
//			output[iterOutput++] = (byte) (input[prevIterInput++] ^ input[iterInput++] ^ key[kpos + 4]);
//			output[iterOutput++] = (byte) (input[prevIterInput++] ^ input[iterInput++] ^ key[kpos + 5]);
//			output[iterOutput++] = (byte) (input[prevIterInput++] ^ input[iterInput++] ^ key[kpos + 6]);
//			output[iterOutput++] = (byte) (input[prevIterInput++] ^ input[iterInput++] ^ key[kpos + 7]);
//		}
//		shiftSessionKey(key, 0, keyLen);
//		return findStopByte(output, iterOutput - blockLen, iterOutput) + 1/*index to size*/;
//	}

	private int decryptBuf(byte[] input, int offset, int length, byte[] key, byte[] iv, byte[] output, int iterOutput) {
		final int blockLen = getBlockLen();
		if (length < blockLen) {
			throw new RuntimeException("Not enough len for at least one block " + length + " vs " + blockLen);
		}
		if (length % blockLen != 0) {
			throw new RuntimeException("Wrong encrypted data len not fit with blockLen " + length + " vs " + blockLen);
		}
		//
		int iterInput = offset;
		final int nBlock = length / blockLen;
		for (int iblock = 0; iblock < nBlock; iblock++) {
			output[iterOutput++] = input[iterInput++];
			output[iterOutput++] = input[iterInput++];
			output[iterOutput++] = input[iterInput++];
			output[iterOutput++] = input[iterInput++];
			output[iterOutput++] = input[iterInput++];
			output[iterOutput++] = input[iterInput++];
			output[iterOutput++] = input[iterInput++];
			output[iterOutput++] = input[iterInput++];
		}
		//
		final int keyLen = getKeyLen();
		shiftSessionKey(key, 0, keyLen);
		return findStopByte(output, iterOutput - blockLen, iterOutput) + 1/*index to size*/;
	}
	
	@Override
	public void shiftSessionKey(byte[] key, int beg, int end) {
		if (end <= beg) {
			return;
		}
		int nshift = key[beg + 2] & 0xff;
		nshift = 1 + nshift % 7;
		int x = key[end - 1] & ((1 << nshift) - 1), y;
		for (int i = beg; i < end; ++i) {
			y = key[i] & 0xff;
			key[i] = (byte) ((y >> nshift) | (x << (8 - nshift)));
			y &= (1 << nshift) - 1;
			x = y;
		}
	}

	@Override
	public byte[] generateSessionKey(byte version, byte[] clientData, byte[] serverData) {
		int clientKeySize = ZTEncryptVersionInfo.Instance.getClientKeySizeByVersion(version);
		int serverKeySize = ZTEncryptVersionInfo.Instance.getServerKeySizeByVersion(version);
		int fromIndexGetClient = (clientData.length - clientKeySize) >> 1;
		int fromIndexGetServer = (serverData.length - serverKeySize) >> 1;
		byte[] sessionKey = new byte[getKeyLen()];
		for (int i = 0; i < sessionKey.length; i += 2) {
			sessionKey[i] = clientData[fromIndexGetClient++];
			sessionKey[i + 1] = serverData[fromIndexGetServer++];
		}
		return sessionKey;
	}

	private int getInt(byte[] input, int it_input) {
		return ((input[it_input] & 0xff) << 24)
				| ((input[it_input + 1] & 0xff) << 16)
				| ((input[it_input + 2] & 0xff) << 8)
				| ((input[it_input + 3] & 0xff));
	}

	@Override
	public int getIVLen() {
		return 8;
	}

	@Override
	public int getBlockLen() {
		return 8;
	}

	@Override
	public int getKeyBlockLen() {
		return 8;
	}

	@Override
	public int getKeyLen() {
		return 32;
	}
}
