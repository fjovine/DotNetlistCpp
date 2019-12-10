#include "DrillScanner.h"
using namespace std;

bool DrillScanner::TryGetHole(int net, PointF & hole) {
	hole = PointF(0.0f, 0.0f);
	float minX = numeric_limits<float>::max();
	float maxX = numeric_limits<float>::min();
	float minY = numeric_limits<float>::max();
	float maxY = numeric_limits<float>::min();

	for (auto segment : drillBitmap.GetSegmentsOfNet(net)) {
		minX = min((float)segment.getXMin(), minX);
		maxX = max((float)segment.getXMax(), maxX);
		minY = min((float)segment.getY(), minY);
		maxY = max((float)segment.getY(), maxY);
	}

	float xSide = 1 + maxX - minX;
	float ySide = 1 + maxY - minY;
	if ((xSide < 2) || (ySide < 2))
	{
		return false;
	}

	if (abs((float)xSide - (float)ySide) / (xSide + ySide) < 0.05)
	{
		hole.X = (maxX + minX) / 2.0f;
		hole.Y = (maxY + minY) / 2.0f;
		return true;
	}

	return false;
}

DrillScanner::DrillScanner(BitmapScanner & bitmapScanner) : drillBitmap(bitmapScanner) {
}

vector<PointF> DrillScanner::GetHoles() {
	if (IsJustInitialized) {
		FindHoles();
		IsJustInitialized = false;
	}
	
	return holes;
}

void DrillScanner::FindHoles() {
	for (auto net : drillBitmap.GetNetIds()) {
		PointF hole(0,0);
		if (TryGetHole(net, hole)) {
			holes.push_back(hole);
		}
	}
}
