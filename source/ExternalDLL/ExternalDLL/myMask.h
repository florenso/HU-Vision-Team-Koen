#pragma once
#include "IntensityImage.h"
#include "ImageFactory.h"
#include <array>
#include <iterator>
#include <cmath>
#include <iostream>

struct mask{ //center is always 0,0
private:
	int offset;//zorgt er voor dat x negatief kan zijn om de array te benaderen
	int width;// om de rij breedte te gebruiken om alles in een array te krijgen..
	int * msk; //dit is de mask array
	int negOffset;

public:
	mask(unsigned int radius) : msk(new int[ (int)pow(( 1 + radius * 2),2) ] ){ //1 = 1 pixel size mask\k & 2=9(3x3)pixelsize mask
		offset = radius;
		negOffset = offset *-1;
		width = 1 + (radius * 2);
	}

	~mask(){
		delete msk;
	}

	void setMask(int * newmask){
		msk = newmask;
	}

	int getpixel(int x, int y){
		return msk[(x + offset) + ((y + offset)*width)];
	}

	void setpixel(int x, int y, int pixel){
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


	//edit de img
	IntensityImage * laplacian(const IntensityImage & img, mask& maskje){
		int width = img.getWidth();
		int height = img.getHeight();
		IntensityImage * newImage = ImageFactory::newIntensityImage(img.getWidth(), img.getHeight());
		const int size = img.getWidth() * img.getHeight();

		for (int x = 0; x < width; x++){
			for (int y = 0; y < height; y++)
			{
				Intensity editPixel = laplacianPixel(img, x, y, maskje);
				newImage->setPixel(x,y, editPixel);
			}
		}


		return newImage;
	}



	//calculeerd intensety
	Intensity laplacianPixel(const IntensityImage &img, unsigned int x, unsigned int y,mask &mask){
		int val = 0;
		for (int x1 = mask.getBegin(); x1 <= mask.getEnd(); x1++){
			for (int y1 = mask.getBegin(); y1 <= mask.getEnd(); y1++){
				if ((x + x1 <= img.getWidth() && x + x1 >= 0) && (y + y1 <= img.getHeight() && y + y1 >= 0)){
					val += (int)img.getPixel(x + x1, y + y1)*(int)mask.getpixel(x1, y1);

				}
				else{
					val += 0;
				}

			}
		}
		if (val < 0){ return (Intensity)0; }
		else if (val>255){ return (Intensity)255; }
		else{
			return (Intensity)val;
		}
		
	
	}
};

