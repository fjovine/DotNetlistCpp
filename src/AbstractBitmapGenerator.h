#ifndef ABSTRACTBITMAPGENERATOR_H
#define ABSTRACTBITMAPGENERATOR_H
#include <string>
#include "Segment.h"

/**
 *  Abstract class able to generate a bitmap.
 *  It must be extended to create a bitmap generator with specific features.
 *  Currently, two subclasses are available, one for compressed PNG bitmaps, the other
 *  for bitmaps rendered as characters, a whitespace for off pixel, a X for on pixels.
 */
class AbstractBitmapGenerator {
private:
	int width;
	int height;

public:
	/**
	 *  Initializes a new instance of the <see cref="AbstractBitmapGenerator"/> class.
	 *  @param width Width of the bitmap in pixel.
	 *  @param height Height of the bitmap in pixel.
	 */
	AbstractBitmapGenerator(int _width, int _height) : width(_width), height(_height) {}
	inline int getWidth() const { return width; }
	inline void setWidth(int value) { width = value; }
	inline int getHeight() const { return height; }
	inline void setHeight(int value) { height = value; }
	void DrawSegment (Segment & segment, int intensity) {
		for (int x = segment.getXMin(); x<=segment.getXMax(); x++) {
			SetPixel(x, segment.getY(), intensity);
		}
	}
	
	virtual void SaveTo(string filename) = 0;
	virtual void SetPixel(int x, int y, int intensity) = 0;
};
#endif
