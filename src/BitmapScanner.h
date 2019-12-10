#ifndef BITMAPSCANNER_H
#define BITMAPSCANNER_H

#include "Scanline.h"
#include "IBitmapAccessor.h"
#include "Segment.h"
#include <vector>
#include <map>

using namespace std;
class BitmapScanner 
{
private:
	IBitmapAccessor * bitmap;
	vector<Segment> segments;
	vector<Scanline> scanlines;
	map<int, vector<Segment>> netlists;
	int find_scanline(int y);
public:
	BitmapScanner(IBitmapAccessor * _bitmap);
	vector<Scanline> GetScanlineIndex();
	vector<Segment> GetSegments();
	vector<Segment> GetSegmentsOfNet(int netId);
	void PrepareAll();
	void Scan();
	void ComputeNetlists();
	int GetNetCount();
	void CompactNets();
	void MapNetlists();
	bool TryGetNetAt(float x, float y, int& netId);
	vector<int> GetNetIds();
};
#endif