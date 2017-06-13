#pragma once
class MessageHidden
{
private:
	MessageHidden();
	~MessageHidden();
public:
	// ��data��������Ϣmessage����\0����β
	static BYTE *hiddenMessageInLSB(BYTE *data, int dataSize, const char *message, int msgSize);
	// ��data�ж�ȡ��Ϣ������message���ɶ�ȡ����ΪmsgSize - 1
	static char *getMessageFromLSB(char *message, int msgSize, const BYTE *data, int dataSize);
	// ��ñ�׼��̬�ֲ�
	static double gaussDistribution();

	static void addGaussNoise(BYTE *data, int dataSize, double mu, double sigma);
};

