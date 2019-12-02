#ifndef SEGMENT_H
#define SEGMENT_H
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
		
		bool Touches(Segment other);
		bool Touches(Segment * other);
		bool ContainsAbscissa(float x);
		friend ostream& operator<<(ostream&, const Segment&);
};
#endif