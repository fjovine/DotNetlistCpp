#include "RealBitmapGenerator.h"

RealBitmapGenerator::RealBitmapGenerator(int _width, int _height) : AbstractBitmapGenerator(_width, _height)
{
	int size = _width * _height * 4;
	image = new vector<unsigned char>(size, 0);
}

RealBitmapGenerator::RealBitmapGenerator(vector <unsigned char> * _image, int _width, int _height) : AbstractBitmapGenerator (_width, _height)
{
	image = new vector<unsigned char>(_image->begin(), _image->end());
}

RealBitmapGenerator::~RealBitmapGenerator() {
	delete image;
}

vector <unsigned char> * RealBitmapGenerator::GetBitmap() {
	return image;
}

void RealBitmapGenerator::SetPixel(int x, int y, int intensity) {
	unsigned color = intensity > 10 ? 0xFFFFFFFF : 0xFF808080;
	int address = 4 * getWidth() * y + 4 * x;
	for (int i=0; i<4; i++) {
		(*image)[address++] = (unsigned char)(color & 0xFF);
		color >>= 8;
	}
}

void RealBitmapGenerator::SaveTo(string filename) {
	int error = lodepng::encode(filename, *image, getWidth(), getHeight());
	if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

void RealBitmapGenerator::CopyBitmap(vector <unsigned char> * toCopy, int x, int y, int width, int height, bool mirror) {
	unsigned char * data_to = image->data();
	unsigned char * data_from = toCopy->data();
	for (int yy = 0; yy<height; yy++) {
		for (int xx = 0; xx < width; xx++) {
			int address_from = 4*(yy * width + xx);
			if (mirror) {
				address_from = 4*(yy * width + (width - xx));
			}
			int address_to = 4 * ((yy+y)*getWidth() + xx+x);
			for (int i=0; i<4; i++) {
				data_to[address_to++] = data_from[address_from++];
			}
		}
	}
}