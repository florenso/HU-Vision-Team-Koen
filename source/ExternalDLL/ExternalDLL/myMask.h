#pragma once
#include "IntensityImage.h"
#include <array>
#include <iterator>
#include <cmath>
#include <iostream>

struct mask{ //center is always 0,0
private:
	int offset;//zorgt er voor dat x negatief kan zijn om de array te benaderen
	int width;// om de rij breedte te gebruiken om alles in een array te krijgen..
	Intensity* msk; //dit is de mask array
	int negOffset;

public:
	mask(unsigned int radius) : msk(new Intensity[ (int)pow(( 1 + radius * 2),2) ] ){ //1 = 1 pixel size mask\k & 2=9(3x3)pixelsize mask
		offset = radius;
		negOffset = offset *-1;
		width = 1 + (radius * 2);
	}

	void setMask(Intensity * newmask){
		msk = newmask;
	}

	unsigned int getpixel(int x, int y){
		return msk[(x + offset) + ((y + offset)*width)];
	}

	void setpixel(int x, int y, Intensity pixel){
		msk[(x + offset) + ((y + offset)*width)] = pixel;
	}

	int getBegin(){//om begin van mask te pakken (voor zowel x als y)
		return negOffset;
	}

	int getEnd(){ // (voor zowel x als y)
		return offset;
	}

	int getWidth(){
		return width;
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
	Intensity laplacianPixel(const IntensityImage &img, unsigned int x, unsigned int y,mask &mask){
		int val = 0;
		for (int x1 = mask.getBegin(); x1 < mask.getEnd(); x1++){
			for (int y1 = mask.getBegin(); y1 < mask.getEnd(); y1++){
				try{
					val += img.getPixel(x + x1, y + y1)*mask.getpixel(x1,y1);
				}
				catch (std::exception ex){
					std::cout << "pixel out of range, make propper catch code for this" << std::endl;
				}
			}
		}
		val = val / pow(mask.getWidth, 2);
		if (val < 0){ return (Intensity)0; }
		return (Intensity)255;
	
	}

	void tmp(){
		Intensity woop[]{
				0, 0, 0, 1, 1, 1, 0, 0, 0,
				0, 0, 0, 1, 1, 1, 0, 0, 0,
				0, 0, 0, 1, 1, 1, 0, 0, 0,
				1, 1, 1, -4, -4, -4, 1, 1, 1,
				1, 1, 1, -4, -4, -4, 1, 1, 1,
				1, 1, 1, -4, -4, -4, 1, 1, 1,
				0, 0, 0, 1, 1, 1, 0, 0, 0,
				0, 0, 0, 1, 1, 1, 0, 0, 0,
				0, 0, 0, 1, 1, 1, 0, 0, 0};

		Intensity woop1[]{
			0,1,0,
			1,-4,1,
			0,1,0
		};
	}
};

