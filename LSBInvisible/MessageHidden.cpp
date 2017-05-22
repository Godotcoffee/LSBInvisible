#include "stdafx.h"
#include "MessageHidden.h"


MessageHidden::MessageHidden()
{
}


MessageHidden::~MessageHidden()
{
}

BYTE *MessageHidden::hiddenMessageInLSB(BYTE *data, int dataSize, const char *message, int msgSize)
{
	const int BYTE_BIT_COUNT = 8;
	int maxSize = dataSize / BYTE_BIT_COUNT;
	for (int i = 0; i < maxSize && i < msgSize; ++i) {
		int ch = message[i];
		int base = i * BYTE_BIT_COUNT;
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
		int base = msgSize * BYTE_BIT_COUNT;
		for (int i = base; i < base + BYTE_BIT_COUNT; ++i) {
			data[i] &= 0xFE;
		}
	}
	return data;
}

char * MessageHidden::getMessageFromLSB(char *message, int msgSize, const BYTE *data, int dataSize)
{
	const int BYTE_BIT_COUNT = 8;
	int hiddenByte = dataSize >> 3;
	for (int i = 0; i < hiddenByte && i < msgSize; ++i) {
		int ch = 0;
		int base = i * BYTE_BIT_COUNT;
		int mask = 1;		// 用作将位置1
		for (int j = base; j < base + BYTE_BIT_COUNT; ++j) {
			if (data[j] & 0x1) {
				ch |= mask;
			}
			mask <<= 1;
		}
		message[i] = ch;
	}
	if (msgSize > hiddenByte) {
		message[hiddenByte] = '\0';
	} else {
		message[msgSize - 1] = '\0';
	}
	return message;
}
