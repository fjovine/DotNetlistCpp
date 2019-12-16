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
	 *  Initializes a new instance of the \ref "AbstractBitmapGenerator" class.
	 *  @param width Width of the bitmap in pixel.
	 *  @param height Height of the bitmap in pixel.
	 */
	AbstractBitmapGenerator(int _width, int _height) : width(_width), height(_height) {}
	/**
	 * Gets or sets the width of the bitmap in pixel.
	 */
	inline int getWidth() const { return width; }
	inline void setWidth(int value) { width = value; }
	/**
	 * Gets or sets the height of the bitmap in pixel.
	 */
	inline int getHeight() const { return height; }
	inline void setHeight(int value) { height = value; }
	
	/** Draws the passed instance of segment.
	 * A \ref "Segment" is a horizontal segment identified during the scan sequence.
	 * 
	 * @param segment Segment to be drawn.
	 * @param intensity The segment is white when intensity is more than 10.
	 */
	void DrawSegment (Segment & segment, int intensity) {
		for (int x = segment.getXMin(); x<=segment.getXMax(); x++) {
			SetPixel(x, segment.getY(), intensity);
		}
	}

	/**
	 * Saves the drawn bitmap to the passed filename.
	 * @param filename Name of the file where the bitmap must be saved. It should have the .png extension.
	 */
	virtual void SaveTo(string filename) = 0;


	/**
	 * Sets a single pixel at the coordinate passed with a white color corresponding to the
	 * intensity value.
	 * @param x Abscissa of the pixel to be set.
	 * @param y Ordinate of the pixel to be set.
	 * @param intensity Intensity of the white pixel.
	 */
	virtual void SetPixel(int x, int y, int intensity) = 0;
};
#endif
