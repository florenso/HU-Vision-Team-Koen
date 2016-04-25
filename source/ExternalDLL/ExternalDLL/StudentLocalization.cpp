#include "StudentLocalization.h"

unsigned int StudentLocalization::headTop(const IntensityImage &image)const{
	unsigned int center = 100;//image.getWidth()/2;
	unsigned int default_y_step = 1;
	unsigned int default_x_step = 1;
	unsigned int lowestValue = image.getHeight();
	std::cout << "center " << center << std::endl;
	while (true){
		//set lowest value
		for (int y = 0; y < image.getHeight(); y += default_y_step){
			std::cout << "y " << y << " intensety " << (int)image.getPixel(center, y) << std::endl;
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
	std::cout << "center " << center << std::endl;
	return lowestValue;
}

bool StudentLocalization::stepFindHead(const IntensityImage &image, FeatureMap &features) const {
	std::cout  << "head begins on: "<< headTop(image) << std::endl;


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