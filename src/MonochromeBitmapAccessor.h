#ifndef MONOCHROMEBITMAPACCESSOR_H
#define MONOCHROMEBITMAPACCESSOR_H
#include "IBitmapAccessor.h"
#include <vector>

/**
 * Describes a real class that implements the \ref "IBitmapAccessor" interface using
 * a png library to read a real bitmap.
 * Following the \ref "https://lodev.org/lodepng/" library, a bitmap is a vector of contiguous 
 * 32 bit words, organized as ttrrggbb, where tt is the transparency byte and the other are the red, green and blue
 * pixel component. The vector is a byte (unsigned char) vector aligned per scanline, so the pixels of each
 * scanline have increasing addresses and the following scanlines occupy following addresses.
 */
class MonochromeBitmapAccessor : public IBitmapAccessor {
private:
	/**
	 * Local store of the bitmap.
	 */
	vector <unsigned char> image;
public:
	/**
	 * Initializes a new instance of the \ref "MonochromeBitmapAccessor" class loading
	 * the bitmap in PNG format from the passed pathname.
	 * @param path Pathname of the bitmap to be loaded.
	 */
	MonochromeBitmapAccessor(const string path);

	/**
	 * Gets a pointer to the bitmap.
	 */
	vector <unsigned char> * GetBitmap();

	/**
	 * Returns true if the pixel at the passed coordinates is set.
	 * @param x Abscissa of the read pixel.
	 * @param y Ordinate of the read pixel.
	 * @return True of the pixel is set.
	 */
	virtual bool pixel_at(int x, int y);

	/**
	 * Sets the pixel at the passed coordinates with the passed color.
	 * @param x Abscissa of the read pixel.
	 * @param y Ordinate of the read pixel.
	 * @param color the color the pixel will have.
	 */
	void set_pixel(int x, int y, int color);
};
#endif