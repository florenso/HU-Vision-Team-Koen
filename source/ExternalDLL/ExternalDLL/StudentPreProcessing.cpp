#include "StudentPreProcessing.h"
#include "IntensityImageStudent.h"
#include "ImageFactory.h"
#include "myMask.h"
#include <minmax.h>

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	IntensityImage * iImg = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	const int size = image.getWidth()* image.getHeight();
		for(int i=0; i < size; i++){
			RGB pixel = image.getPixel(i);
			Intensity grayPixel = (max(pixel.r, pixel.g, pixel.b) + min(pixel.r, pixel.g, pixel.b)) / 2;
			//Intensity grayPixel = (pixel.b + pixel.g + pixel.r) / 3;
			//Intensity grayPixel = (pixel.b*0.0722 + pixel.g*0.7152 + pixel.r*0.2126);
			iImg->setPixel(i, grayPixel);			
		}
	return iImg;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	myMask ConvertoEdges = myMask();
	int woop[]{
			0, 0, 0, 1, 1, 1, 0, 0, 0,
			0, 0, 0, 1, 1, 1, 0, 0, 0,
			0, 0, 0, 1, 1, 1, 0, 0, 0,
			1, 1, 1, -4, -4, -4, 1, 1, 1,
			1, 1, 1, -4, -4, -4, 1, 1, 1,
			1, 1, 1, -4, -4, -4, 1, 1, 1,
			0, 0, 0, 1, 1, 1, 0, 0, 0,
			0, 0, 0, 1, 1, 1, 0, 0, 0,
			0, 0, 0, 1, 1, 1, 0, 0, 0};

	int woop1[]{
			0, 1, 0,
			1, -4, 1,
			0, 1, 0
	};

	mask UsingMask = mask(4);
	UsingMask.setMask(woop);
	
	IntensityImage * ing = ConvertoEdges.laplacian(image, UsingMask);

	return ing;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}