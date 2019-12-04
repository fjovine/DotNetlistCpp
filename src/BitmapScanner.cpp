#include "BitmapScanner.h"

using namespace std;

BitmapScanner::BitmapScanner(IBitmapAccessor _bitmap) {
   bitmap = _bitmap;
}

vector<Scanline> BitmapScanner::GetScanlineIndex() {
	return scanlines;
}

vector<Segment> BitmapScanner::GetSegments() {
	return segments;
}

vector<Segment> BitmapScanner::GetSegmentsOfNet(int netId) {
	return netlists[netId];
}

void BitmapScanner::PrepareAll() {
	Scan();
	ComputeNetlists();
	CompactNets();
	MapNetlists();
}

void BitmapScanner::Scan() {
	Segment currentSegment;
	bool isSegmentOpen = false;
	
	for (int y=0; y<bitmap.get_height(); y++) {
	}
}

void BitmapScanner::ComputeNetlists() {
}

int BitmapScanner::GetNetCount() {
}

void BitmapScanner::CompactNets() {
}

void BitmapScanner::MapNetlists() {
}

bool BitmapScanner::TryGetNetAt(float x, float y, int& netId) {
}

vector<int> BitmapScanner::GetNetIds() {
}
