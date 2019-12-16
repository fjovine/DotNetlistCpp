#ifndef IBITMAPACCESSOR_H
#define IBITMAPACCESSOR_H
#include <iostream>

using namespace std;

/**
 * Describes a simple access to a virtual bitmap.
 */
class IBitmapAccessor 
{
protected:
	int width;
	int height;
public:
	/**
	 * Gets and sets the horizontal size of the bitmap in pixel.
	 */
	inline int get_width() const { return width; }
	inline void set_width(int value) { width = value; }

	/*
	 * Gets the vertical size of the bitmap in pixel.
	 */
	inline int get_height() const { return height; }
	inline void set_height(int value) { height = value; }

	/**
	 * Bitmaps are monochromatic, i.e. either a bit is set or not.
	 * This function determines the presence of a set bit.
	 * @param x Abscissa of the pixel.
	 * @param y Ordinate of the pixel.
	 * @return True if the bit is set.
	 */
	virtual bool pixel_at(int x, int y)
	{
		cout << "IBitmapAccessor.1" << endl;
		throw invalid_argument("Unimplemented virtual method");
	}
};
#endif