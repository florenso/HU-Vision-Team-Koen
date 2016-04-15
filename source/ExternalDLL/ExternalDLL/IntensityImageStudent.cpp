#include "IntensityImageStudent.h"

IntensityImageStudent::IntensityImageStudent() : IntensityImage() {
	img = new Intensity[1]{Intensity{ 0 }};
}

IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &other) : IntensityImage(other.getWidth(), other.getHeight()) {
	img = new Intensity[getWidth()*getHeight()]{Intensity{ 0 }};
	
}

IntensityImageStudent::IntensityImageStudent(const int width, const int height) : IntensityImage(width, height) {
	img = new Intensity[width*height]{Intensity{ 0 }};
}

IntensityImageStudent::~IntensityImageStudent() {
	delete[] img;
}

void IntensityImageStudent::set(const int width, const int height) {
	int oldWidth = getWidth();
	int oldHeight = getHeight();
	IntensityImage::set(width, height);
	translateToNewWith(oldHeight, oldHeight, width, height);
	
}

void IntensityImageStudent::set(const IntensityImageStudent &other) {
	int oldWidth = getWidth();
	int oldHeight = getHeight();
	IntensityImage::set(other.getWidth(), other.getHeight());
	translateToNewWith(oldHeight, oldHeight, other.getWidth(), other.getHeight());
}

void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
	setPixel(x+(y*getWidth()),pixel);
}

void IntensityImageStudent::setPixel(int i, Intensity pixel) {
	img[i] = pixel;
}

Intensity IntensityImageStudent::getPixel(int x, int y) const {
	return getPixel(x + (y*getWidth()));
}

Intensity IntensityImageStudent::getPixel(int i) const {
	return img[i];
}

void IntensityImageStudent::translateToNewWith(int oldWidth, int oldheight, int newWidth, int newHeight){
	if (newWidth > oldheight){
		Intensity * newImg;
		newImg = new Intensity[newHeight*newWidth]{Intensity{ 0 }};
		for (int i = oldheight*oldWidth; i >= 0; --i){
			newImg[i + (((int)i / newWidth)*(newWidth - oldWidth))] = img[i];

		}
		delete[] img;
		img = newImg;
	}
}