#pragma once
class MessageHidden
{
private:
	MessageHidden();
	~MessageHidden();
public:
	static BYTE *hiddenMessageInLSB(BYTE *data, int dataSize, const BYTE *message, int msgSize);
	static BYTE *getMessageFromLSB(BYTE *message, int msgSize, const BYTE *data, int dataSize);
};

