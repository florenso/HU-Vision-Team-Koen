#include "StudentLocalization.h"
#include <algorithm>
#include "RGBImage.h"
#include "ImageFactory.h"
#include "HereBeDragons.h"
#include "ImageIO.h"

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
	int centerXaxis = features.getFeature(Feature::FEATURE_HEAD_TOP).getX();
	int possibleCenterYaxis = imageIn.getHeight() / 2;
	int stepY = 1;
	int stepX = 2;
	int margeCenterLeftRight = 5; //in the middle of the image, some points are ignored 5 + 5 = 10.
	std::map <int, int> numberOfPixelsPerXaxisHalfLeftSide{};
	std::map <int, int> numberOfPixelsPerXaxisHalfRightSide{};

	for (int dX = 0; dX < width; dX += stepX){
		for (int dY = 0; dY < height; dY += stepY){
			Intensity currentPixel = imageIn.getPixel(dX, dY);
			if (currentPixel == 0){
				if (dX <= (centerXaxis - margeCenterLeftRight)){ //left side of head with marge
					numberOfPixelsPerXaxisHalfLeftSide[dX] = numberOfPixelsPerXaxisHalfLeftSide[dX] + 1;
				} 
				else if (dX >= (centerXaxis + margeCenterLeftRight)){ //right side of head with marge
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


	features.putFeature(Feature(Feature::FEATURE_HEAD_LEFT_SIDE, Point2D<double>(leftSideXaxis, 116.0)));
	features.putFeature(Feature(Feature::FEATURE_HEAD_RIGHT_SIDE, Point2D<double>(rightSideXaxis, 116.0)));

	std::cout << "Left Side location x-axis:  (" << features.getFeature(Feature::FEATURE_HEAD_LEFT_SIDE).getX() << ", " << features.getFeature(Feature::FEATURE_HEAD_LEFT_SIDE).getY() << ")\n";
	std::cout << "Right Side location x-axis:  (" << features.getFeature(Feature::FEATURE_HEAD_RIGHT_SIDE).getX() << ", " << features.getFeature(Feature::FEATURE_HEAD_RIGHT_SIDE).getY() << ")\n";
	std::cout << "Top head location x-axis: (" << features.getFeature(Feature::FEATURE_HEAD_TOP).getX() << ", " << features.getFeature(Feature::FEATURE_HEAD_TOP).getY() << ")\n";

		

	//int highestValueLeftSide = numberOfPixelsPerXaxis

	//for (auto it = numberOfPixelsPerXaxis.cbegin(); it != numberOfPixelsPerXaxis.cend(); ++it)
	//{
	//	std::cout << it->first << " --> " << it->second << "\n";
	//}

	IntensityImage * image = ImageFactory::newIntensityImage();
	HereBeDragons::SonnetCLI(imageIn, *image);

	ImageIO::saveIntensityImage(*image, ImageIO::getDebugFileName("Localization-1/nose-removed.png"));

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

	//working images:

	//child-1.png
	//female-1.png
	//female-3.png == but NOT WORKING with Arno's version, we made it better :) I added an option for middle marge.
	//male-3.png
	//bouke-1.png == but NOT WORKING with Arno's version.
	

	//not working:
	//female-2.png == but working with Arno's working
	//male-1.png == but working with Arno's verion.
	//male-2.png == but working with Arno's verion.
	//koen-2.png == NOT WORKING
	//arno-1.png == NOT WORKING.

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
