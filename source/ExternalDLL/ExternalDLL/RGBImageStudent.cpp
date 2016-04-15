#include "RGBImageStudent.h"

RGBImageStudent::RGBImageStudent() : RGBImage() {
	img = new RGB[0];
}

RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) : RGBImage(other.getWidth(), other.getHeight()) {
	img = new RGB[getWidth()*getHeight()];
}


RGBImageStudent::RGBImageStudent(const int width, const int height) : RGBImage(width, height) {
	img = new RGB[width*height];
}

RGBImageStudent::~RGBImageStudent() {
	delete[] img;
}

void RGBImageStudent::set(const int width, const int height) {
	int oldWidth = getWidth();
	int oldHeight = getHeight();
	RGBImage::set(width, height);
	translateToNewWith(oldHeight, oldHeight, width, height);
}

void RGBImageStudent::set(const RGBImageStudent &other) {
	int oldWidth = getWidth();
	int oldHeight = getHeight();
	RGBImage::set(other.getWidth(), other.getHeight());
	translateToNewWith(oldHeight, oldHeight, other.getWidth(), other.getHeight());
}

void RGBImageStudent::setPixel(int x, int y, RGB pixel) {
	setPixel(x + (y*getWidth()), pixel);
}

void RGBImageStudent::setPixel(int i, RGB pixel) {
	img[i] = pixel;
}

RGB RGBImageStudent::getPixel(int x, int y) const {
	return getPixel(x + (y*getWidth()));
}

RGB RGBImageStudent::getPixel(int i) const {
	return img[i];
}

void RGBImageStudent::translateToNewWith(int oldWidth, int oldheight, int newWidth, int newHeight){
	if (newWidth > oldheight){
		img = new RGB[newHeight*newWidth];
		for (int i = oldheight*oldWidth; i >= 0; --i){
			img[i + (((int)i / newWidth)*(newWidth - oldWidth))] = img[i];
			img[i] = RGB::RGB(0,0,0);
		}
	}
}