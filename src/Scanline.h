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
		int getY() const;
		void setY(int _y);
		int getInitialIndex() const;
		void setInitialIndex(int _initialIndex);
		int getLength() const;
		void incLength();
		void setLength(int _length);
		friend std::ostream& operator<<(std::ostream&, const Scanline&);
		void Foreach(vector<Segment> & segments, function<void(Segment &)> iterator);
		vector<Segment> GetTouchingSegments(vector<Segment> & segments, const Segment & segment);
		void BackPropagate(vector<Segment> & segments, int newNetlist, int oldNetlist) const;
		Scanline(int _y, int _initialIndex);
};

#endif
