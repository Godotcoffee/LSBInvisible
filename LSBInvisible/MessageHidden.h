#pragma once
class MessageHidden
{
private:
	MessageHidden();
	~MessageHidden();

	template<typename T>
	static void shuffleArrayByKey(T* arr, int size, unsigned int key);
public:
	// ��data��������Ϣmessage����\0����β
	static BYTE *hiddenMessageInLSB(BYTE *data, int dataSize, const char *message, int msgSize, bool useKey = false, unsigned int key = 0);
	// ��data�ж�ȡ��Ϣ������message���ɶ�ȡ����ΪmsgSize - 1
	static char *getMessageFromLSB(char *message, int msgSize, const BYTE *data, int dataSize, bool useKey = false, unsigned int key = 0);
	// ��ñ�׼��̬�ֲ�
	static double getGaussRandom();
	// ��Ӹ�˹����
	static void addGaussNoise(BYTE *data, int dataSize, double mu, double sigma);
	// ELFHash�㷨
	static UINT32 elfHash(const char *str);
};

template<typename T>
void inline MessageHidden::MessageHidden::shuffleArrayByKey(T* arr, int size, unsigned int key)
{
	// PRN����
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