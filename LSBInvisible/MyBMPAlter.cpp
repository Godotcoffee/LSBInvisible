#include "stdafx.h"

#include "MyBMPAlter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <windows.h>

using std::ifstream;
using std::ofstream;
using std::ios_base;
using std::ostringstream;
using std::cerr;
using std::endl;
using std::cout;
using std::abs;

MyBMPAlter::MyBMPAlter()
	: isRead(false), quad(NULL), quadSize(0), imageData(NULL), imageSize(0)
{
}

MyBMPAlter::MyBMPAlter(const char *fileName)
	: isRead(false), quad(NULL), quadSize(0), imageData(NULL), imageSize(0)
{
	ifstream bmpInput = ifstream(fileName, ios_base::in | ios_base::binary);
	if (!bmpInput) {
		// 打开失败
		cerr << "Can't open " << fileName << endl;
		return;
	}
	// 读取文件头
	bmpInput.read((char *)&fileHeader, sizeof(fileHeader));
	// 读取信息头
	bmpInput.read((char *)&infoHeader, sizeof(infoHeader));
	if (infoHeader.biBitCount < 24) {
		// 24位以下需要读取调色板
		// 调色板大小
		int totByte = 1 << infoHeader.biBitCount;
		quad = new RGBQUAD[totByte];
		if (quad == NULL) {
			bmpInput.close();
			cerr << "Can't allocate memory of " << totByte << "bytes" << endl;
			return;
		}
		bmpInput.read((char *)quad, totByte * sizeof(RGBQUAD));
		quadSize = totByte;
	}
	// 每行原始需要的位数
	int bitPerRow = infoHeader.biBitCount * infoHeader.biWidth;
	// 进行4字节（32位）对齐
	// bytePerRow = ((bitPerRow + 31) / 32 * 32) / 8
	int extBytePerRow = (bitPerRow + 31) >> 5 << 2;
	// 高度有可能为负
	int totByte = extBytePerRow * abs(infoHeader.biHeight);
	imageData = new BYTE[totByte];
	if (imageData == NULL) {
		bmpInput.close();
		cerr << "Can't allocate memory of " << totByte << "bytes" << endl;
		return;
	}
	bmpInput.read((char *)imageData, totByte * sizeof(BYTE));
	imageSize = totByte;

	bmpInput.close();
	isRead = true;
}

MyBMPAlter::MyBMPAlter(const string fileName) : MyBMPAlter(fileName.c_str())
{
}

MyBMPAlter::MyBMPAlter(const BITMAPFILEHEADER &fileHeader, const BITMAPINFOHEADER &infoHeader, const RGBQUAD *quad, int quadSize, const BYTE *imageData, int imageSize)
	: isRead(false), fileHeader(fileHeader), infoHeader(infoHeader), quadSize(quadSize), imageSize(imageSize)
{
	if ((this->quad = new RGBQUAD[quadSize]) == NULL) {
		cerr << "Can't allocate memory of " << quadSize << "bytes" << endl;
		return;
	}
	memcpy(this->quad, quad, quadSize * sizeof(RGBQUAD));

	if ((this->imageData = new BYTE[imageSize]) == NULL) {
		cerr << "Can't allocate memory of " << imageSize << "bytes" << endl;
		return;
	}
	memcpy(this->imageData, imageData, imageSize * sizeof(BYTE));

	isRead = true;
}

MyBMPAlter::MyBMPAlter(const MyBMPAlter &bmp) noexcept : isRead(false), quad(NULL), imageData(NULL)
{
	fileHeader = bmp.fileHeader;
	infoHeader = bmp.infoHeader;
	quadSize = bmp.quadSize;
	if (quadSize > 0) {
		if ((quad = new RGBQUAD[quadSize]) != NULL) {
			memcpy(quad, bmp.quad, quadSize * sizeof(RGBQUAD));
		} else {
			cerr << "Can't allocate memory of " << quadSize << "bytes" << endl;
			return;
		}
	}
	imageSize = bmp.imageSize;
	if (imageSize > 0) {
		if ((imageData = new BYTE[imageSize]) != NULL) {
			memcpy(imageData, bmp.imageData, imageSize * sizeof(BYTE));
		} else {
			cerr << "Can't allocate memory of " << imageSize << "bytes" << endl;
			return;
		}
	}
	isRead = bmp.isRead;
}

MyBMPAlter::MyBMPAlter(MyBMPAlter &&bmp) noexcept
{
	// 先判断是否是同一个地址的对象
	if (this != &bmp) {
		isRead = bmp.isRead;
		fileHeader = bmp.fileHeader;
		infoHeader = bmp.infoHeader;
		quad = bmp.quad;
		quadSize = bmp.quadSize;
		imageData = bmp.imageData;
		imageSize = bmp.imageSize;
		bmp.quad = NULL;
		bmp.imageData = NULL;
	}
}

MyBMPAlter &MyBMPAlter::operator=(const MyBMPAlter &bmp) noexcept
{
	// 先判断是否是同一个地址的对象
	if (this != &bmp) {
		this->~MyBMPAlter();
		isRead = false;
		fileHeader = bmp.fileHeader;
		infoHeader = bmp.infoHeader;
		quadSize = bmp.quadSize;
		if (quadSize > 0) {
			if ((quad = new RGBQUAD[quadSize]) != NULL) {
				memcpy(quad, bmp.quad, quadSize * sizeof(RGBQUAD));
			} else {
				cerr << "Can't allocate memory of " << quadSize << "bytes" << endl;
				return *this;
			}
		}
		imageSize = bmp.imageSize;
		if (imageSize > 0) {
			if ((imageData = new BYTE[imageSize]) != NULL) {
				memcpy(imageData, bmp.imageData, imageSize * sizeof(BYTE));
			} else {
				cerr << "Can't allocate memory of " << imageSize << "bytes" << endl;
				return *this;
			}
		}

		isRead = bmp.isRead;
	}
	return *this;
}

MyBMPAlter & MyBMPAlter::operator=(MyBMPAlter &&bmp) noexcept
{
	// 先判断是否是同一个地址的对象
	if (this != &bmp) {
		this->~MyBMPAlter();
		isRead = bmp.isRead;
		fileHeader = bmp.fileHeader;
		infoHeader = bmp.infoHeader;
		quad = bmp.quad;
		quadSize = bmp.quadSize;
		imageData = bmp.imageData;
		imageSize = bmp.imageSize;
		bmp.quad = NULL;
		bmp.imageData = NULL;
	}
	return *this;
}

MyBMPAlter::~MyBMPAlter() noexcept
{
	delete[] quad;
	delete[] imageData;
	quad = NULL;
	imageData = NULL;
}

bool MyBMPAlter::checkIsRead() const
{
	return isRead;
}

bool MyBMPAlter::operator!() const
{
	return !isRead;
}

void MyBMPAlter::outputInfo() const
{
	outputInfo(cout);
}

void MyBMPAlter::outputInfo(ostream& os) const
{
	os << "======FileHeader======" << endl;
	os << "File Type:       " << fileHeader.bfType << endl;
	os << "File Size:       " << fileHeader.bfSize << endl;
	os << "Offset:          " << fileHeader.bfOffBits << endl;
	os << "======InfoHeader======" << endl;
	os << "InfoHeader Size: " << infoHeader.biSize << endl;
	os << "Image Width:     " << infoHeader.biWidth << endl;
	os << "Image Height:    " << infoHeader.biHeight << endl;
	os << "Planes:          " << infoHeader.biPlanes << endl;
	os << "Bit Count:       " << infoHeader.biBitCount << endl;
	os << "Compression:     " << infoHeader.biCompression << endl;
	os << "Image Size:      " << infoHeader.biSizeImage << endl;
	os << "XPels Per Meter: " << infoHeader.biXPelsPerMeter << endl;
	os << "YPels Per Meter: " << infoHeader.biYPelsPerMeter << endl;
	os << "Color Used:      " << infoHeader.biClrUsed << endl;
	os << "Color Important: " << infoHeader.biClrImportant << endl;
}

ostream &operator<<(ostream &os, const MyBMPAlter &bmp)
{
	bmp.outputInfo(os);
	return os;
}

const BITMAPFILEHEADER &MyBMPAlter::getFileHeader() const
{
	return fileHeader;
}

const BITMAPINFOHEADER &MyBMPAlter::getInfoHeader() const
{
	return infoHeader;
}

const RGBQUAD *MyBMPAlter::getQuad() const
{
	return quad;
}

int MyBMPAlter::getQuadSize() const
{
	return quadSize;
}

const BYTE *MyBMPAlter::getImageData() const
{
	return imageData;
}

int MyBMPAlter::getImageSize() const
{
	return imageSize;
}

bool MyBMPAlter::saveAsFile(const char *fileName) const
{
	ofstream bmpOutput(fileName, ios_base::out | ios_base::binary);
	if (!bmpOutput) {
		cerr << "Can't open " << fileName << endl;
		return false;
	}
	bmpOutput.write((char *)&fileHeader, sizeof(fileHeader));
	bmpOutput.write((char *)&infoHeader, sizeof(infoHeader));
	bmpOutput.write((char *)quad, quadSize * sizeof(RGBQUAD));
	bmpOutput.write((char *)imageData, imageSize * sizeof(BYTE));
	bmpOutput.close();
	return true;
}

bool MyBMPAlter::saveAsFile(const string fileName) const
{
	return saveAsFile(fileName.c_str());
}
