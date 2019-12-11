#ifndef POINTF_H
#define POINTF_H
#include <iostream>

using namespace std;
class PointF {
public:
	float X;
	float Y;
	PointF (float _X, float _Y) : X(_X), Y(_Y) {};
	inline friend ostream& operator<<(ostream & os, const PointF & p) {
		return os << "(" << p.X << "," << p.Y << ") ";
	}
};
#endif
