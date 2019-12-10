#include "BitmapScanner.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

BitmapScanner::BitmapScanner(IBitmapAccessor * _bitmap) : bitmap(_bitmap)
{
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
		
	for (int y=0; y<bitmap->get_height(); y++) {
		Scanline currentScanline(y, segments.size());
		bool previousPixel = false;
		for (int x=0; x<=bitmap->get_width(); x++) {
			bool currentPixel = x < bitmap->get_width() ? bitmap->pixel_at(x, y) : false;
			if (!previousPixel && currentPixel)
			{
				// Console.WriteLine($"Start at {x}");
				// Starts a contiguous segment
				currentSegment = Segment(y, x,  x);
				isSegmentOpen = true;
			}
			
			if (previousPixel && !currentPixel)
			{
				// Console.WriteLine($"End at {x-1}");
				// Ends a contiguous segment
				assert(isSegmentOpen);
				currentSegment.setXMax(x - 1);
				currentScanline.incLength();
				segments.push_back(currentSegment);
				isSegmentOpen = false;
			}
			previousPixel = currentPixel;
		}
		
		if (currentScanline.getLength() > 0) {
			scanlines.push_back(currentScanline);
		}
	}
}

void BitmapScanner::ComputeNetlists() {
	int netlist = 1;
	Scanline * ppreviousScanline = NULL;
	Scanline previousScanline(0,0);
	for (Scanline scanline : scanlines)
	{	
		scanline.Foreach(
			segments,
			[&netlist, ppreviousScanline, scanline, this](Segment &segment) {
				segment.setNetList(netlist ++);
				if ((ppreviousScanline == NULL) || (ppreviousScanline->getY() < scanline.getY()-1)) {
					return;
				}
				
				auto touchingSegments = ppreviousScanline->GetTouchingSegments(segments, segment);
				bool isFirst =  true;
				for (auto touchingSegment : touchingSegments) {
					if (isFirst) {
						segment.setNetList(touchingSegment.getNetList());
						isFirst = false;
					}
					else
					{
						scanline.BackPropagate(segments, segment.getNetList(), touchingSegment.getNetList());
					}
				}
			}
		);
		previousScanline = scanline;
		ppreviousScanline = & previousScanline;
	}
}

int BitmapScanner::GetNetCount() {
	return netlists.size();
}

void BitmapScanner::CompactNets() {
	auto nets = map<int, int>();
	int sequential = 1;
	
	for (auto segment : segments) {
		auto found = nets.find(segment.getNetList());
		if (found == nets.end()) {
			auto thePair = pair<int,int>(segment.getNetList(), sequential++);
			nets.insert(thePair);
		}
	}
	
	for (int i=0; i<segments.size(); i++) {
		int originalNetlist = segments[i].getNetList();
		int newNetlist = nets[originalNetlist];
		segments[i].setNetList(newNetlist);
	}
}

void BitmapScanner::MapNetlists() {
	for (auto segment : segments) {
		auto netId = segment.getNetList();
		auto found = netlists.find(netId);
		if (found == netlists.end()) {
			netlists[netId] = vector<Segment>();
		}
		
		netlists[netId].push_back(segment);
	}	
}

bool BitmapScanner::TryGetNetAt(float x, float y, int& netId) {
	int index = find_scanline(y);
	netId = 1;
	
	if (index < 0) {
		return false;
	}
	
	Scanline found = scanlines[index];
	for (int i=0; i<found.getLength(); i++) {
		Segment segment = segments[found.getInitialIndex()+i];
		if (segment.ContainsAbscissa(x)) {
			netId = segment.getNetList();
			return true;
		}
	}
	
	return false;
}

vector<int> BitmapScanner::GetNetIds() {
	vector<int> result;
	
	for (auto pair : netlists) {
		result.push_back(pair.first);
	}
	return result;
}

int BitmapScanner::find_scanline(int y) {
	int result = -1;
	int i = 0;
	for (auto scanline : scanlines) {
		if (scanline.getY() == y) {
			result = i;
			break;
		}
		
		i++;
	}
	
	return result;
}
