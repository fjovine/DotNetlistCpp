#include "Scanline.h"

int Scanline::getY() {
	return y;
}

void Scanline::setY(int _y) {
	y = _y;
}

int Scanline::getInitialIndex() {
	return initialIndex;
}

void Scanline::setInitialIndex(int _initialIndex) {
	initialIndex = _initialIndex;
}

int Scanline::getLength() {
	return length;
}

void Scanline::setLength(int _length) {
	length = _length;
}

ostream& operator<<(ostream& os, const Scanline& s)
{
	return os << s.y << "-(" << s.initialIndex << "," << s.length << ")";
}

void Scanline::Foreach(vector<Segment> & segments, function<void(const Segment)> iterator) {
	for (int i=0; i<length; i++) {
		iterator(segments[i+initialIndex]);
	}
}

vector<Segment> Scanline::GetTouchingSegments(vector<Segment> & segments, const Segment & segment) {
	vector<Segment> result;

	for (int i=0; i<length; i++) {
		Segment s = segments[i+initialIndex];
		if (segment.Touches(s)) {
				result.push_back(s); 
		}
	}
	
	return result;
}
