#include "Segment.h"

int Segment::getY() {
	return y;
}

void Segment::setY(int yy) {
	y = yy;
}

int Segment::getXMin() {
	return xMin;
}

void Segment::setXMin(int xmin) {
	xMin = xmin;
}

int Segment::getXMax() {
	return xMax;
}

void Segment::setXMax( int xmax) {
	xMax = xmax;
}

int Segment::getNetList()
{
	return netList;
}

void Segment::setNetList(int netlist)
{
	netList = netlist;
}

bool Segment::Touches(const Segment & other) const
{
	if (y != other.y+1) {
		return false;
	}
	
	if (other.xMax < xMin) {
		return false;
	}
	
	if (other.xMin > xMax) {
		return false;
	}
	
	return true;
}

bool Segment::ContainsAbscissa(float x)
{
	return (xMin <= x) && (xMax >= x);
} 

ostream& operator<<(ostream& os, const Segment& s)
{
	return os << s.y << "," << s.xMin << "-" << s.xMax << "," << s.netList;
}

Segment::Segment(int y, int xmin, int xmax)
{
	setY(y);
	setXMin(xmin);
	setXMax(xmax);
}

Segment::Segment() : Segment(0,0,0) {
}