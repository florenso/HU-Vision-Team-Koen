#include "StudentPreProcessing.h"
#include "IntensityImageStudent.h"

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	IntensityImageStudent * iImg = new IntensityImageStudent(image.getWidth(), image.getHeight());
	const int size = image.getWidth()* image.getHeight();
		for(int i=0; i < size; i++){
			RGB pixel = image.getPixel(i);
			Intensity grayPixel = (pixel.b + pixel.g + pixel.r) / 3;
			//Intensity grayPixel = (pixel.b*0.0722 + pixel.g*0.7152 + pixel.r*0.2126);
			iImg->setPixel(i, grayPixel);			
		}
	return iImg;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}