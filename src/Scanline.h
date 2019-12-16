#ifndef SCANLINE_H
#define SCANLINE_H
#include <functional>
#include <vector>
#include "Segment.h"
using namespace std;

/**
 * Describes the segments composing a scan line,
 * While scanning a scan line, a number of segments are generated that are sequentially stored in
 * a segment list.
 * So the scan line holds the index of the first one.
 */
class Scanline
{
	private:
		int y;
		int initialIndex;
		int length;
	public:
		/**
		 * Gets or sets the ordinate of the scan line. All the segments composing the scan line share this same value.
		 */
		int getY() const;
		void setY(int _y);

		/**
		 * Gets or sets the index of the first segment in the corresponding segment list that belongs to this scan line.
		 */
		int getInitialIndex() const;
		void setInitialIndex(int _initialIndex);

		/**
		 * Gets or sets the number of subsequent segments that belong to this scan line.
		 */
		int getLength() const;
		void setLength(int _length);

		/**
		 * Increments the number of subsequent segments that belong to this scan line.
		 */
		void incLength();

		/**
		 * Builds a textual representation of the object and outputs it to stdout.
		 * @return The textual representation of the object.</returns>
		 */
		friend std::ostream& operator<<(std::ostream&, const Scanline&);

		/**
		 * Iterates in the list of segments belonging to the scan line in the passed segment list.
		 * @param "segments" The list of segments composing the bitmap.
		 * @param "iterator" Lambda action that is applied to each segment.
		 */
		void Foreach(vector<Segment> & segments, function<void(Segment &)> iterator);

		/**
		 * Returns the list of segment touched by the passed segment.
		 * This is the list of segments having one less ordinate, that share at least one pixel having the same abscissa with the passed segment.
		 * @param "segments" List of segments composing the scanned bitmap.
		 * @param "segment" The segment that must be analyzed.
		 * @return The list of segments touched by the passed one.
		 */
		vector<Segment> GetTouchingSegments(vector<Segment> & segments, const Segment & segment);

		/**
		 * Propagates back the new net id.
		 * This method is called whenever a new segment makes a short circuit between segments that have already a net identifier.
		 * It iterates back in the segment list and changes the old net into the new one. At the end of the process all the
		 * connected segment have the new net identifier.
		 * @param segments List of the scanned segments.</param>
		 * @param newNetlist Old net identifier.</param>
		 * @param oldNetlist New net identifier.</param>
		*/
		void BackPropagate(vector<Segment> & segments, int newNetlist, int oldNetlist) const;

		/**
		 * Initializes a new instance of the \res "Scanline" class.
		 * @param _y Ordinate of the scanline
		 * @param _initialIndex Index of the first segment in the scanline at the passed ordinate.
		 */
		Scanline(int _y, int _initialIndex);
};

#endif
