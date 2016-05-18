#pragma once
#include "IntensityImage.h"
#include <array>
#include <iterator>
#include <cmath>

struct mask{ //center is always 0,0
private:
	int offset;//zorgt er voor dat x negatief kan zijn om de array te benaderen
	int width;// om de rij breedte te gebruiken om alles in een array te krijgen..
	Intensity* msk; //dit is de mask array

public:
	mask(unsigned int radius) : msk(new Intensity[ (int)pow(( 1 + radius * 2),2) ] ){ //1 = 1 pixel size mask\k & 2=9(3x3)pixelsize mask
		offset = radius;
		width = 1 + (radius * 2);
	}
	unsigned int getpixel(int x, int y){
		return msk[(x + offset) + ((y + offset)*width)];
	}

	void setpixel(int x, int y, Intensity pixel){
		msk[(x + offset) + ((y + offset)*width)] = pixel;
	}


	int getBegin(){//om begin van mask te pakken (voor zowel x als y)
		return offset*-1;
	}

	int getEnd(){ // (voor zowel x als y)
		return offset;
	}


	
};

class myMask
{
public:
	myMask();
	~myMask();

	//edit de img
	void laplacian(IntensityImage *img, mask& mask);

	//calculeerd intensety
	Intensity laplacianPixel(IntensityImage &img, unsigned int x, unsigned int y, mask &mask){
		int val = 0;
		for (int x1 = mask.getBegin(); x1 < mask.getEnd(); x1++){
			for (int y1 = mask.getBegin(); y1 < mask.getEnd(); y1++){

			}
		}
	
	}
};

