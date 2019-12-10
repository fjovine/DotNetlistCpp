#include "Scanline.h"
using namespace std;

int Scanline::getY() const {
	return y;
}

void Scanline::setY(int _y) {
	y = _y;
}

int Scanline::getInitialIndex() const {
	return initialIndex;
}

void Scanline::setInitialIndex(int _initialIndex) {
	initialIndex = _initialIndex;
}

int Scanline::getLength() const {
	return length;
}

void Scanline::setLength(int _length) {
	length = _length;
}

ostream& operator<<(ostream& os, const Scanline& s)
{
	return os << s.y << "-(" << s.initialIndex << "," << s.length << ")";
}

void Scanline::Foreach(vector<Segment> & segments, function<void(Segment &)> iterator) {
	for (int i=0; i<length; i++) {
		iterator(segments[i+initialIndex]);
	}
}

vector<Segment> Scanline::GetTouchingSegments(vector<Segment> & segments, const Segment & segment) {	
	vector<Segment> result;

	
	for (int i=0; i<length; i++) {
		Segment s = segments[i+initialIndex];
		bool touches = segment.Touches(s);
		if (touches) {
			result.push_back(s); 
		}
	}
	
	return result;
}

void Scanline::BackPropagate(vector<Segment> & segments, int newNetlist, int oldNetlist) const
{
	if (newNetlist == oldNetlist) {
		return;
	}
	
	for (int segmentIndex = initialIndex + length - 1; segmentIndex >= 0; segmentIndex--)
	{
		if (segments[segmentIndex].getNetList() == oldNetlist)
		{
			segments[segmentIndex].setNetList(newNetlist);
		}
	}
}


Scanline::Scanline(int _y, int _initialIndex) : y(_y), initialIndex(_initialIndex), length(0) {}

void Scanline::incLength()
{
	length++;
}