#ifndef SEGMENT_H
#define SEGMENT_H
#include <iostream>

using namespace std;
class Segment {
	private:
		int y;
		int xMin;
		int xMax;
		int netList;
	public:
		int getY();
		void setY(int yy);
		int getXMin();
		void setXMin(int xmin);
		int getXMax();
		void setXMax(int xmax);
		int getNetList();
		void setNetList(int netlist);
		
		bool Touches(const Segment & other) const;
		bool ContainsAbscissa(float x);
		friend ostream& operator<<(ostream& os, const Segment& s);
		
		Segment(int y, int ymin, int ymax);
		Segment();
};
#endif