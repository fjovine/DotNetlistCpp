#ifndef REALBITMAPGENERATOR
#define REALBITMAPGENERATOR
#include "AbstractBitmapGenerator.h"
#include "../lodepng/lodepng.h"
#include <string>

class RealBitmapGenerator : public AbstractBitmapGenerator {
protected:
	vector <unsigned char> * image;
public:
	RealBitmapGenerator(int _width, int _height);
	~RealBitmapGenerator();
	RealBitmapGenerator(vector <unsigned char> * _image,int _width, int _height);
	vector <unsigned char> * GetBitmap();
	void CopyBitmap(vector <unsigned char> * image, int x, int y, int width, int height, bool mirror = false);
	virtual void SetPixel(int x, int y, int intensity);
	virtual void SaveTo(string filename);
};

#endif