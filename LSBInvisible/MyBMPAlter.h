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
	MyBMPAlter(const BITMAPFILEHEADER &fileHeader, const BITMAPINFOHEADER &infoHeader, const RGBQUAD *quad, int quadSize, const BYTE *imageData, int imageSize); // 自定义Bitmap数据构造函数
	MyBMPAlter(const MyBMPAlter &bmp) noexcept;
	MyBMPAlter(MyBMPAlter &&bmp) noexcept;		// 移动构造函数
	MyBMPAlter &operator=(const MyBMPAlter &bmp) noexcept;
	MyBMPAlter &operator=(MyBMPAlter &&bmp) noexcept;	// 移动赋值函数

	virtual ~MyBMPAlter() noexcept;

	/* 检查是否成功读取 */
	bool checkIsRead() const;
	bool operator!() const;

	/* 输出图片信息 */
	void outputInfo() const;
	void outputInfo(ostream &os) const;
	friend ostream &operator<<(ostream &os, const MyBMPAlter &bmp);

	/* 获得图片的相关数据 */
	const BITMAPFILEHEADER &getFileHeader() const;
	const BITMAPINFOHEADER &getInfoHeader() const;
	const RGBQUAD *getQuad() const;
	int getQuadSize() const;
	const BYTE *getImageData() const;
	int getImageSize() const;

	/* 保存至文件 */
	bool saveAsFile(const char *fileName) const;
	bool saveAsFile(const string fileName) const;
};
