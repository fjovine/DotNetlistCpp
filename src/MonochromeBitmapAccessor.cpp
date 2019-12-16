#include "MonochromeBitmapAccessor.h"
#include "../lodepng/lodepng.h"

MonochromeBitmapAccessor::MonochromeBitmapAccessor(const string path) {
	unsigned width, height;
	int error = lodepng::decode(image, width, height, path);
	if (error) {
		cout << "decoder error " << error << ": " << lodepng_error_text(error) << " on file " << path << endl;
		throw "Problems decoding a PNG file";
	}
	set_width(width);
	set_height(height);
cout << "MonochromeBitmapAccessor : path " << path << " width "	<< width << " height " << height <<" size " << image.size() << endl;
}

vector <unsigned char> * MonochromeBitmapAccessor::GetBitmap() {
	return & image;
}

bool MonochromeBitmapAccessor::pixel_at(int x, int y) {
	int address = 4 * get_width() * y + 4 * x;
	int r = image[address++];
	int g = image[address++];
	int b = image[address];
	return (r > 10) || (g > 10) || (b > 10);
}

void MonochromeBitmapAccessor::set_pixel(int x, int y, int color)
{
	int address = 4 * get_width() * y + 4 * x;
	for (int i=0; i<4; i++) {
		image[address++] = (unsigned char)(color & 0xFF);
		color >>= 8;
	}
}
