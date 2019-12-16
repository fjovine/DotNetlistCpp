#ifndef MONOCHROMEBITMAPACCESSOR_H
#define MONOCHROMEBITMAPACCESSOR_H
#include "IBitmapAccessor.h"
#include <vector>
class MonochromeBitmapAccessor : public IBitmapAccessor {
private:
	vector <unsigned char> image;
public:
	MonochromeBitmapAccessor(const string path);
	vector <unsigned char> * GetBitmap();
	virtual bool pixel_at(int x, int y);
	void set_pixel(int x, int y, int color);
};
#endif