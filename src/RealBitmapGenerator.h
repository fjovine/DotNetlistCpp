#ifndef REALBITMAPGENERATOR
#define REALBITMAPGENERATOR
#include "AbstractBitmapGenerator.h"
#include "../lodepng/lodepng.h"
#include <string>

/**
 * Real implementation of the \ref "AbstractBitmapGenerator" for a real bitmap
 * backed up by a PNG image file.
 */
class RealBitmapGenerator : public AbstractBitmapGenerator {
protected:
	vector <unsigned char> * image;
public:
	/**
	 * Initializes a new instance of the \ref "RealBitmapGenerator" class.
	 * @param _width Width of the bitmap in pixels.
	 * @param _height Height of the bitmap in pixels.
	 */
	RealBitmapGenerator(int _width, int _height);

	/**
	 * Delets the instance, freeing the memory used by the bitmap image.
	 */
	~RealBitmapGenerator();

	/**
	 * <summary>
	 * Initializes a new instance of the \ref "RealBitmapGenerator"
	 * The bitmap is a clone of an existing one.
	 * @param "_image">The initial bitmap from which new pixels will be set or reset.
	 * @param _width Width of the bitmap in pixels.
	 * @param _height Height of the bitmap in pixels.
	 */
	RealBitmapGenerator(vector <unsigned char> * _image,int _width, int _height);

	/**
	 * Gets the current bitmap.
	 * @return The current bitmap.
	 */
	vector <unsigned char> * GetBitmap();

	/**
	 * Copies the passed bitmap to the passed position of this bitmap, possibly mirroring (around the vertical axis) the passed bitmap.
	 * @param image bitmap to be copied to this bitmap.
	 * @param x abscissa of the destination top, left point, to which the bitmap is copied.
	 * @param y ordinate of the destination top, left point, to which the bitmap is copied.
	 * @param width of the copied bitmap.
	 * @param height of the copied bitmap.
	 * @param mirror if true, the copied bitmap is mirrored.
	 */
	void CopyBitmap(vector <unsigned char> * image, int x, int y, int width, int height, bool mirror = false);

	/**
	 * Sets a pixel at the specified coordinates with the passed intensity.
	 * @param x Abscissa of the pixel to set.</param>
	 * @param y Ordinate of the pixel to set.</param>
	 * @param intensity Intensity of the pixel. If > 10 the pixel will be white.</param>
	 */
	virtual void SetPixel(int x, int y, int intensity);

	/**
	 * Saves the generated bitmap to a PNG file.
	 * @param "filename" Name of the file where the bitmap will be saved.
	 */
	virtual void SaveTo(string filename);
};

#endif