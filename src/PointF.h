#ifndef POINTF_H
#define POINTF_H
#include <iostream>

using namespace std;
/**
 * Descibes a point having floating point coordinates.
 */
class PointF {
public:
	/**
	 * Abscissa of the point.
	 */
	float X;

	/**
	 * Ordinate of the point.
	 */
	float Y;

	/**
	 * Initializes a new point with the passed coordinates.
	 * @param _X abscissa of the point.
	 * @param _Y ordinate of the point.
	 */
	PointF (float _X, float _Y) : X(_X), Y(_Y) {};

	/**
	 * Outputs on stout a readable version of an object of this class 
	 * in the traditional geometrical format (x,y) for points.
	 */
	inline friend ostream& operator<<(ostream & os, const PointF & p) {
		return os << "(" << p.X << "," << p.Y << ") ";
	}
};
#endif
