#include "StudentExtraction.h"



bool StudentExtraction::stepExtractEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentExtraction::stepExtractNose(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentExtraction::stepExtractMouth(const IntensityImage &image, FeatureMap &features) const {
	std::cout << "has FEATURE_MOUTH_CENTER " << features.getFeature(Feature::FEATURE_MOUTH_CENTER).getY() << std::endl;
	std::cout << "has FEATURE_MOUTH_BOTTOM " << features.getFeature(Feature::FEATURE_MOUTH_BOTTOM).getY() << std::endl;
	std::cout << "has FEATURE_MOUTH_TOP " << features.getFeature(Feature::FEATURE_MOUTH_TOP).getY() << std::endl;
	return false;
}