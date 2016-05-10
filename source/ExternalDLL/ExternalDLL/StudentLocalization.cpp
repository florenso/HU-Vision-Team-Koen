#include "StudentLocalization.h"
#include <algorithm>
#include "RGBImage.h"
#include "ImageFactory.h"
#include "HereBeDragons.h"
#include "ImageIO.h"

struct pixelCount {
	pixelCount(int leftCount, int middelCount,int rightCount){
		left = leftCount;
		middel = middelCount;
		right = rightCount;
	}
	//pixelCount(const IntensityImage &image,int y ,int left, int middel, int right,){}
	int left;
	int middel;
	int right;
};

Feature StudentLocalization::headTop(const IntensityImage &image) const{
	unsigned int center = image.getWidth()/2;
	const unsigned int default_y_step = 1;
	const unsigned int default_x_step = 5;
	unsigned int lowestValue = image.getHeight();
	//std::cout << "starting center " << center << std::endl;
	while (true){
		//set lowest value
		for (int y = 0; y < image.getHeight(); y += default_y_step){
			//std::cout << "y " << y << " intensety " << (int)image.getPixel(center, y) << std::endl;
			if (image.getPixel(center, y) < 50){
				lowestValue = y;
				break;
			}
		}
		

		//check left
		unsigned int left;
		for (int y = 0; y < image.getHeight(); y += default_y_step){
			if (image.getPixel(center - default_x_step , y) < 50){
				left = y;
				break;
			}
		}

		//check right
		unsigned int right;
		for (int y = 0; y < image.getHeight(); y += default_y_step){
			if (image.getPixel(center + default_x_step, y) < 50){
				right = y;
				break;
			}
		}
		//std::cout << "left " << left << std::endl;
		//std::cout << "pivot " << lowestValue << std::endl;
		//std::cout << "right " << right << std::endl;
		if (left < right){
			if (left < lowestValue){
				center -= default_x_step;
				lowestValue = left;
			}
			else{ break; }
		}
		else {
			if (right < lowestValue){
				center += default_x_step;
				lowestValue = right;
			}
			else{ break; }
		}
	}
	//std::cout << "final center " << center << std::endl;
	//std::cout << "head begins on: " << lowestValue << std::endl;
	return Feature{ Feature::FEATURE_HEAD_TOP, Point2D<double>(center, lowestValue) };
}

bool StudentLocalization::stepFindHead(const IntensityImage &imageIn, FeatureMap &features) const {

	features.putFeature(headTop(imageIn));
	
	int width = imageIn.getWidth();
	int height = imageIn.getHeight();
	int headTopX = features.getFeature(Feature::FEATURE_HEAD_TOP).getX();
	int headTopY = features.getFeature(Feature::FEATURE_HEAD_TOP).getY();
	int percentageForHead = 30;
	

	int possibleCenterYaxis = imageIn.getHeight() / 2;
	int stepY = 1;
	int stepX = 2;
	int margeCenterLeftRight = 5; //in the middle of the image, some points are ignored 5 + 5 = 10.
	int margeLeftAndRight = 6;
	int stepTwoY = 4;
	int stepTwoX = 1;

	std::map <int, int> numberOfPixelsPerXaxisHalfLeftSide{};
	std::map <int, int> numberOfPixelsPerXaxisHalfRightSide{};

	for (int dX = 0; dX < width; dX += stepX){
		for (int dY = 0; dY < (height - headTopY); dY += stepY){
			Intensity currentPixel = imageIn.getPixel(dX, dY);
			if (currentPixel == 0){
				if (dX <= (headTopX - margeCenterLeftRight)){ //left side of head with marge
					numberOfPixelsPerXaxisHalfLeftSide[dX] = numberOfPixelsPerXaxisHalfLeftSide[dX] + 1;
				} 
				else if (dX >= (headTopX + margeCenterLeftRight)){ //right side of head with marge
					numberOfPixelsPerXaxisHalfRightSide[dX] = numberOfPixelsPerXaxisHalfRightSide[dX] + 1;
				}
			}
		}
	}

	int leftSideXaxis = std::max_element(numberOfPixelsPerXaxisHalfLeftSide.begin(), numberOfPixelsPerXaxisHalfLeftSide.end(),
		[](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
		return p1.second < p2.second; })->first;

	int rightSideXaxis = std::max_element(numberOfPixelsPerXaxisHalfRightSide.begin(), numberOfPixelsPerXaxisHalfRightSide.end(),
		[](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
		return p1.second < p2.second; })->first;

	//test code koen
	const int whiteCountMax = 25;

	int y = features.getFeature(Feature::FEATURE_HEAD_TOP).getY();
	//seek first pixel
	for (y; y < imageIn.getHeight(); ++y){
		if (imageIn.getPixel(leftSideXaxis, y) < 50){
			break;
		}
	}
	std::cout << "line begins on y: " << y << " on x:" << leftSideXaxis << std::endl;
	//seek last pixel
	int whiteCount = 0;
	int lastPixelAt = 0;
	for (y; y < imageIn.getHeight(); ++y){
		++whiteCount;
		//if pixel is black....
		if (imageIn.getPixel(leftSideXaxis, y) < 50){
			whiteCount = 0;
			lastPixelAt = y;
			std::cout << "found black pixel @ " << y << std::endl;
		}
		if (whiteCount>whiteCountMax){
			break;
		}

	}
	int leftLastPixelAt = lastPixelAt;

	std::cout << "doing right side" << std::endl;
	y = 0;
	for (y; y < imageIn.getHeight(); ++y){
		if (imageIn.getPixel(rightSideXaxis, y) < 50){
			break;
		}
	}
	 whiteCount = 0;
	 lastPixelAt = 0;
	for (y; y < imageIn.getHeight(); ++y){
		++whiteCount;
		//if pixel is black....
		if (imageIn.getPixel(rightSideXaxis, y) < 50){
			whiteCount = 0;
			lastPixelAt = y;
			std::cout << "found black pixel @ " << y << std::endl;
		}
		if (whiteCount>whiteCountMax){
			break;
		}

	}
	int rightLastPixelAt = lastPixelAt;

	if (leftLastPixelAt<rightLastPixelAt){
		lastPixelAt = leftLastPixelAt;
	}


	std::cout << "last pixel @: " << lastPixelAt << std::endl;

	features.putFeature(Feature(Feature::FEATURE_HEAD_LEFT_SIDE, Point2D<double>(leftSideXaxis, lastPixelAt)));
	features.putFeature(Feature(Feature::FEATURE_HEAD_RIGHT_SIDE, Point2D<double>(rightSideXaxis, lastPixelAt)));


	std::cout << "Left Side location x-axis:  (" << features.getFeature(Feature::FEATURE_HEAD_LEFT_SIDE).getX() << ", " << features.getFeature(Feature::FEATURE_HEAD_LEFT_SIDE).getY() << ")\n";
	std::cout << "Right Side location x-axis:  (" << features.getFeature(Feature::FEATURE_HEAD_RIGHT_SIDE).getX() << ", " << features.getFeature(Feature::FEATURE_HEAD_RIGHT_SIDE).getY() << ")\n";
	std::cout << "Top head location x-axis: (" << features.getFeature(Feature::FEATURE_HEAD_TOP).getX() << ", " << features.getFeature(Feature::FEATURE_HEAD_TOP).getY() << ")\n";


	IntensityImage * image = ImageFactory::newIntensityImage();
	HereBeDragons::SonnetCLI(imageIn, *image);

	cv::Mat outImage;
	HereBeDragons::HerLoveForWhoseDearLoveIRiseAndFall(*image, outImage);
	cv::cvtColor(outImage, outImage, CV_GRAY2RGB);

	
	cv::circle(outImage, cv::Point((int)features.getFeature(Feature::FEATURE_HEAD_TOP).getX(), (int)features.getFeature(Feature::FEATURE_HEAD_TOP).getY()), 4, cv::Scalar(0, 0, 255), -1, 8);
	cv::circle(outImage, cv::Point((int)features.getFeature(Feature::FEATURE_HEAD_LEFT_SIDE).getX(), (int)features.getFeature(Feature::FEATURE_HEAD_LEFT_SIDE).getY()), 4, cv::Scalar(0, 0, 255), -1, 8);
	cv::circle(outImage, cv::Point((int)features.getFeature(Feature::FEATURE_HEAD_RIGHT_SIDE).getX(), (int)features.getFeature(Feature::FEATURE_HEAD_RIGHT_SIDE).getY()), 4, cv::Scalar(0, 0, 255), -1, 8);
	

	//Save debug image
	RGBImage * outImageRGB = ImageFactory::newRGBImage();
	HereBeDragons::HeIsContentedThyPoorDrudgeToBe(outImage, *outImageRGB);
	ImageIO::saveRGBImage(*outImageRGB, ImageIO::getDebugFileName("Localization-1/debug.png"));
	delete outImageRGB;
	delete image;

	return true;
}

bool StudentLocalization::stepFindNoseMouthAndChin(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindChinContours(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindNoseEndsAndEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindExactEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}
