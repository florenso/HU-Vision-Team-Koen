#include "StudentLocalization.h"
#include <algorithm>

Feature StudentLocalization::headTop(const IntensityImage &image)const{
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

bool StudentLocalization::stepFindHead(const IntensityImage &image, FeatureMap &features) const {

	features.putFeature(headTop(image));
	
	int width = image.getWidth();
	int height = image.getHeight();
	int possibleCenterXaxis = image.getWidth() / 2;
	int possibleCenterYaxis = image.getHeight() / 2;
	int stepY = 1;
	int stepX = 2;
	std::map <int, int> numberOfPixelsPerXaxisHalfLeftSide{};
	std::map <int, int> numberOfPixelsPerXaxisHalfRightSide{};

	for (int dX = 0; dX < width; dX += stepX){
		for (int dY = 0; dY < height; dY += stepY){
			Intensity currentPixel = image.getPixel(dX, dY);
			if (currentPixel == 0){
				if (dX <= possibleCenterXaxis){ //possible left side 
					numberOfPixelsPerXaxisHalfLeftSide[dX] = numberOfPixelsPerXaxisHalfLeftSide[dX] + 1;
				} 
				else{ //possible right side
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

	std::cout << "Left Side location x-axis: " << leftSideXaxis << "\n";
	std::cout << "Right Side location x-axis: " << rightSideXaxis << "\n";
	
	features.putFeature(Feature(Feature::FEATURE_HEAD_LEFT_SIDE, Point2D<double>(leftSideXaxis, 142.0)));
	features.putFeature(Feature(Feature::FEATURE_HEAD_TOP, Point2D<double>(95.0, 8.0)));
	features.putFeature(Feature(Feature::FEATURE_HEAD_RIGHT_SIDE, Point2D<double>(rightSideXaxis, 142.0)));
		

	//int highestValueLeftSide = numberOfPixelsPerXaxis

	//for (auto it = numberOfPixelsPerXaxis.cbegin(); it != numberOfPixelsPerXaxis.cend(); ++it)
	//{
	//	std::cout << it->first << " --> " << it->second << "\n";
	//}


	//std::cout << "Pixel on 3,3 " << "\n" << int(kippetje) << "\n";

	/*
	cv::circle(outImage, cv::Point((int)headTop.getPoints()[0].x, (int)headTop.getPoints()[0].y), 1, cv::Scalar(0, 0, 255), -1, 8);
	cv::circle(outImage, cv::Point((int)headLeftSide.getPoints()[0].x, (int)headLeftSide.getPoints()[0].y), 1, cv::Scalar(0, 0, 255), -1, 8);
	cv::circle(outImage, cv::Point((int)headRightSide.getPoints()[0].x, (int)headRightSide.getPoints()[0].y), 1, cv::Scalar(0, 0, 255), -1, 8);

	//Save debug image
	RGBImage * outImageRGB = ImageFactory::newRGBImage();
	HereBeDragons::HeIsContentedThyPoorDrudgeToBe(outImage, *outImageRGB);
	ImageIO::saveRGBImage(*outImageRGB, ImageIO::getDebugFileName("Localization-1/debug.png"));
	delete outImageRGB;
	delete image;


	ImageIO::saveIntensityImage(*executor->resultPreProcessingStep4, ImageIO::getDebugFileName("Pre-processing-4.png"));
	*/
	//ImageIO::saveRGBImage(*outImageRGB, ImageIO::getDebugFileName("Localization-1/debug.png"));


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
