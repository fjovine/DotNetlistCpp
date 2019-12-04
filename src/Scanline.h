#ifndef SCANLINE_H
#define SCANLINE_H
#include <functional>
#include <vector>
#include "Segment.h"
using namespace std;

class Scanline
{
	private:
		int y;
		int initialIndex;
		int length;
	public:
		int getY();
		void setY(int _y);
		int getInitialIndex();
		void setInitialIndex(int _initialIndex);
		int getLength();
		void setLength(int _length);
		friend std::ostream& operator<<(std::ostream&, const Scanline&);
		void Foreach(vector<Segment> & segments, function<void(Segment &)> iterator);
		vector<Segment> GetTouchingSegments(vector<Segment> & segments, Segment & segment);
};

#endif
