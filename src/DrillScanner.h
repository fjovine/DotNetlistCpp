#ifndef DRILLSCANNER_H
#define DRILLSCANNER_H
#include "BitmapScanner.h"
#include "PointF.h"
#include <limits>
#include <cmath>

/**
 * This class recognizes the holes from a \see "BitmapScanner" object passed.
 * When a drill bitmap is scanned, it results as nets that extend each hole.
 * This class scans each net, checks if it is a hole (i.e.if it can be inscribed
 * in a square) and generates a list of coordinates for each hole.
 */
class DrillScanner {
private:
	bool IsJustInitialized = true;
	/**
	 * Local scanner of the drill layer.
	 */
	BitmapScanner drillBitmap;

	/**
	 * Private list of the hole coordinates.
	 */
	vector<PointF> holes;

	/**
	 * Checks whether the passed net can represent a hole.
	 * It may be possible that the drill layer contains also other signs, like the outline, that are not real holes.
	 * 
	 * @param net" Net it found on the drill layer.
	 * @param hole" Point where the hole lies.
	 * @return True if the net represents a hole.
	 */
	bool TryGetHole(int net, PointF & hole);

	/**
	 * Finds all the holes on the layer.
	 */
	void FindHoles();
public:
	/**
	 * Initializes a new instance of the \ref="DrillScanner"
	 * @param drillBitmap BitmapScanner that has already processed the drill bitmap.
	 */
	DrillScanner(BitmapScanner & bitmapScanner);

	/**
	 * Computes all the holes returning their coordinates.
	 * A hole is indeed a set of scan lines connected, i.e. a net. There is one test done: the minimum rectangle that
	 * includes the net must be square with sides measuring more than 2 pixels..
	 * The list of points where the holes are.
	 */
	vector<PointF> GetHoles();
};
#endif