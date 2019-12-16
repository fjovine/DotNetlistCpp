#ifndef SEGMENT_H
#define SEGMENT_H
#include <iostream>

using namespace std;

/**
 * Represents a horizontal segment of continuous copper on the
 * PCB.
 */
class Segment {
	private:
		int y;
		int xMin;
		int xMax;
		int netList;
	public:
		/**
		 * Gets or sets the ordinate of the segment.
		 * As the segment is horizontal, this ordinate is common to all the points
		 * composing the segment.
		 */
		int getY();
		void setY(int yy);

		/**
		 * Gets or sets the minimum abscissa of the horizontal segment.
		 */
		int getXMin();
		void setXMin(int xmin);

		/**
		 * Gets or sets the maximum abscissa of the horizontal segment.
		 */
		int getXMax();
		void setXMax(int xmax);

		/**
		 * Gets or sets the net index the segment belongs to.
		 */
		int getNetList() const;
		void setNetList(int netlist);

		/**
		 *  Computes whether the current segment touches another one.
		 *  A segment touches another segment if and only if
		 *  * the ordinate of the segments differ of 1 pixel, i.e. they are contiguous vertically
		 *  * there is at least one pixel having the same abscissa in common between the segments.
		 *
		 * @param name "other" The segment that is verified.
		 * @returns True if this segment touches the other one.
		 */
		bool Touches(const Segment & other) const;

		/**
		 * Returns true if the segment contains the passed abscissa.
		 * @param x Abscissa to be checked.
		 * @returns True if the abscissa is contained in the segment.</returns>
		 */
		bool ContainsAbscissa(float x);

		/**
		 * Outputs on stout a readable version of an object of this class composed by
		 * the ordinate, the min and max abscissa separated by a dash and ending with the netlist code.
		 */
		friend ostream& operator<<(ostream& os, const Segment& s);

		/**
		 * Initializes a new instance of the \ref Segment class.
		 * @param xmin minimal abscissa of the segment.
		 * @param xnax maximal abscissa of the segment.
		 */
		Segment(int y, int xmin, int xmax);
		
		/**
		 * Initializes a new instance of the \ref Segment class.
		 */
		Segment();
};
#endif