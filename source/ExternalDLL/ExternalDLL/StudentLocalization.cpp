#include "StudentLocalization.h"

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