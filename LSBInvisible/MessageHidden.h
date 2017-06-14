#pragma once
class MessageHidden
{
private:
	MessageHidden();
	~MessageHidden();

	template<typename T>
	static void shuffleArrayByKey(T* arr, int size, unsigned int key);
public:
	// 往data中隐藏信息message，以\0作结尾
	static BYTE *hiddenMessageInLSB(BYTE *data, int dataSize, const char *message, int msgSize, bool useKey = false, unsigned int key = 0);
	// 从data中读取信息保存至message，可读取长度为msgSize - 1
	static char *getMessageFromLSB(char *message, int msgSize, const BYTE *data, int dataSize, bool useKey = false, unsigned int key = 0);
	// 获得标准正态分布
	static double getGaussRandom();
	// 添加高斯噪声
	static void addGaussNoise(BYTE *data, int dataSize, double mu, double sigma);
	// ELFHash算法
	static UINT32 elfHash(const char *str);
};

template<typename T>
void inline MessageHidden::MessageHidden::shuffleArrayByKey(T* arr, int size, unsigned int key)
{
	// PRN参数
	static const int A = 1664525, C = 1013904223;
	unsigned int x = key;

	for (int i = 0; i < size - 1; ++i) {
		INT64 x64 = x;
		x = x64 * A + C;
		int pos = i + x % (size - i);
		T tmp = arr[i];
		arr[i] = arr[pos];
		arr[pos] = tmp;
	}
}