#include "stdafx.h"
#include "MessageHidden.h"

#include <fstream>

MessageHidden::MessageHidden()
{
}


MessageHidden::~MessageHidden()
{
}


BYTE *MessageHidden::hiddenMessageInLSB(BYTE *data, int dataSize, const char *message, int msgSize, bool useKey, unsigned int key)
{
	const int BYTE_BIT_COUNT = 8;
	int maxSize = dataSize / BYTE_BIT_COUNT;
	int *indexArr = nullptr;
	if (useKey && (indexArr = new int[maxSize]) == nullptr) {
		return nullptr;
	}
	if (useKey) {
		for (int i = 0; i < maxSize; ++i) {
			indexArr[i] = i;
		}
		shuffleArrayByKey(indexArr, maxSize, key);
	}

	for (int i = 0; i < maxSize && i < msgSize; ++i) {
		int ch = message[i];
		int base = (useKey ? indexArr[i] : i) * BYTE_BIT_COUNT;
		for (int j = base; j < base + BYTE_BIT_COUNT; ++j) {
			if (ch & 0x1) {
				data[j] |= 0x1;
			} else {
				data[j] &= 0xFE;
			}
			ch >>= 1;
		}
	}
	// 插入\0
	if (msgSize < maxSize) {
		int base = (useKey ? indexArr[msgSize] : msgSize) * BYTE_BIT_COUNT;
		for (int i = base; i < base + BYTE_BIT_COUNT; ++i) {
			data[i] &= 0xFE;
		}
	}

	delete[] indexArr;
	return data;
}

char *MessageHidden::getMessageFromLSB(char *message, int msgSize, const BYTE *data, int dataSize, bool useKey, unsigned int key)
{
	const int BYTE_BIT_COUNT = 8;
	int hiddenByte = dataSize >> 3;

	int *indexArr = nullptr;
	if (useKey && (indexArr = new int[hiddenByte]) == nullptr) {
		return nullptr;
	}
	if (useKey) {
		for (int i = 0; i < hiddenByte; ++i) {
			indexArr[i] = i;
		}
		shuffleArrayByKey(indexArr, hiddenByte, key);
	}

	for (int i = 0; i < hiddenByte && i < msgSize; ++i) {
		int ch = 0;
		int base = (useKey ? indexArr[i] : i) * BYTE_BIT_COUNT;
		int mask = 1;		// 用作将位置1
		for (int j = base; j < base + BYTE_BIT_COUNT; ++j) {
			if (data[j] & 0x1) {
				ch |= mask;
			}
			mask <<= 1;
		}
		message[i] = ch;
	}

	// \0
	if (msgSize > hiddenByte) {
		message[hiddenByte] = '\0';
	} else {
		message[msgSize - 1] = '\0';
	}
	return message;
}

double MessageHidden::getGaussRandom()
{
	// Box-Muller
	static const double PI = 6 * asin(0.5);
	static const int ACCURATE = RAND_MAX;
	double randNum1 = rand() % ACCURATE * 1.0 / ACCURATE;
	double randNum2 = rand() % ACCURATE * 1.0 / ACCURATE;
	return sqrt(-2.0 * log(randNum1)) * sin(PI * 2 * randNum2);
}

void MessageHidden::addGaussNoise(BYTE *data, int dataSize, double mu, double sigmaSquare)
{
	double sigma = sqrt(sigmaSquare);
	for (int i = 0; i < dataSize; ++i) {
		int val = data[i] & BYTE_MAX;
		val = std::round(val + getGaussRandom() * sigma + mu);		// 四舍五入，避免浮点数精度误差
		data[i] = (BYTE) max(0, min(BYTE_MAX, val));
	}
}

UINT32 MessageHidden::elfHash(const char *str)
{
	UINT32 hash = 0;
	UINT32 x = 0;

	while (*str) {
		hash = (hash << 4) + *str++;
		if (x = hash & 0xF0000000) {
			hash ^= x >> 24;
			hash &= ~x;		// 不理解资料中这一步为什么要把高4位清0
		}
	}

	return hash;
}
