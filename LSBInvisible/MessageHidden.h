#pragma once
class MessageHidden
{
private:
	MessageHidden();
	~MessageHidden();
public:
	// 往data中隐藏信息message，以\0作结尾
	static BYTE *hiddenMessageInLSB(BYTE *data, int dataSize, const char *message, int msgSize);
	// 从data中读取信息保存至message，可读取长度为msgSize - 1
	static char *getMessageFromLSB(char *message, int msgSize, const BYTE *data, int dataSize);
};

