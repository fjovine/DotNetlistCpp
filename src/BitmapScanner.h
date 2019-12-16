#ifndef BITMAPSCANNER_H
#define BITMAPSCANNER_H

#include "Scanline.h"
#include "IBitmapAccessor.h"
#include "Segment.h"
#include <vector>
#include <map>

using namespace std;
/**
 * This class implements the algorithm of scanning the passed bitmap.
 * It starts from the topmost \ref="Scanline" and builds all the segments, connecting them to each net as soon as a relation of being touched
 * by other segments is found.
 */
class BitmapScanner 
{
private:
	/**
     * Local repository of the bitmap being scanned.
	 */
	IBitmapAccessor * bitmap;
	
	/**
	 * List of segments found.
	 */
	vector<Segment> segments;
	
	/**
	 * List of horizontal scan lines composing the bitmap.
	 */
	vector<Scanline> scanlines;
	
	/**
	 * Maps a net identifier to the list of segments belonging to that net.
	 * This means that all the segments in each list are electrically connected with all the others.
	 */
	map<int, vector<Segment>> netlists;
	
	/**
	 * linear search the first scanline having the passed ordinate.
	 * @param y the ordinate of the first scanline.
	 * @return the index of the first scanline with the passed ordinate.
	 */
	int find_scanline(int y);
public:
    /**
	 * Initializes a new instance of the \ref="BitmapScanner"/> class, ready to scan the passed bitmap.
	 * @param _bitmap to be scanned.
	 */
	BitmapScanner(IBitmapAccessor * _bitmap);
	
	/**
	 * Gets the list of scan lines.
     */
	vector<Scanline> GetScanlineIndex();
	
	/**
	 *  Gets the list of segments scanned in this bitmap.
	 */
	vector<Segment> GetSegments();
	
	/**
	 * Gets the list of segments belonging to the passed net.
	 * @param netId net identifier to be used in the search.
	 * @return the list of segment belonging to the  passed net.
	 */
	vector<Segment> GetSegmentsOfNet(int netId);
	
	/**
	 * Prepares the net list, i.e. computes them, compacts the, i.e. reduces the net identifiers to consecutive
	 * numbers.
	 */
	void PrepareAll();
	
	/**
	 * Scans the bitmap, i.e. builds the list of scanned segments.
	 */
	void Scan();
	
	/**
	 * Checks which segments are connected together and sets an identical net identifier to all of them.
	 */
	void ComputeNetlists();
	
	/**
	 * Computes the number of nets found.
	 * @return the number of nets found.
	 */
	int GetNetCount();
	
	/**
     * After having checked which segments are electrically connected, the net identifiers are non sequential integers.
     * This method compacts them so that all the net identifiers are sequential integers starting from 1.
	 */
	void CompactNets();
	
	/**
     * After the net identifiers have been computed, fills the dictionary <see cref="netlists"/> that map every net identifier to the
     * list of segments composing the net.
	 */
	void MapNetlists();
	
	/**
	 *  Returns true if the passed point is inside a net.
	 *  If this is the case, then the net id is passed
	 *  to the out parameter.
	 * 
	 *  @parar xAbscissa of the point to check.
	 *  @param y Ordinate of the point to check
	 *  @param netId Numeric net identifier of the net touched by the point, if any.
	 *  @return True if the passed point lies inside a net, i.e. copper.
	 */
	bool TryGetNetAt(float x, float y, int& netId);

	/**
     *  Gets the list of available net identifiers.
	 *
	 *  @ retur The list of available net identifiers.
	 */	
	vector<int> GetNetIds();
};
#endif