#pragma once
#include <windows.h>
#include <string>

using std::string;
using std::ostream;

class MyBMPAlter {
protected:
	bool isRead;
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	RGBQUAD *quad;
	int quadSize;
	BYTE *imageData;
	int imageSize;
public:
	MyBMPAlter();
	MyBMPAlter(const char *fileName);
	MyBMPAlter(const string fileName);
	MyBMPAlter(const BITMAPFILEHEADER &fileHeader, const BITMAPINFOHEADER &infoHeader, const RGBQUAD *quad, int quadSize, const BYTE *imageData, int imageSize); // �Զ���Bitmap���ݹ��캯��
	MyBMPAlter(const MyBMPAlter &bmp) noexcept;
	MyBMPAlter(MyBMPAlter &&bmp) noexcept;		// �ƶ����캯��
	MyBMPAlter &operator=(const MyBMPAlter &bmp) noexcept;
	MyBMPAlter &operator=(MyBMPAlter &&bmp) noexcept;	// �ƶ���ֵ����

	virtual ~MyBMPAlter() noexcept;

	/* ����Ƿ�ɹ���ȡ */
	bool checkIsRead() const;
	bool operator!() const;

	/* ���ͼƬ��Ϣ */
	void outputInfo() const;
	void outputInfo(ostream &os) const;
	friend ostream &operator<<(ostream &os, const MyBMPAlter &bmp);

	/* ���ͼƬ��������� */
	const BITMAPFILEHEADER &getFileHeader() const;
	const BITMAPINFOHEADER &getInfoHeader() const;
	const RGBQUAD *getQuad() const;
	int getQuadSize() const;
	const BYTE *getImageData() const;
	int getImageSize() const;

	/* �������ļ� */
	bool saveAsFile(const char *fileName) const;
	bool saveAsFile(const string fileName) const;
};
