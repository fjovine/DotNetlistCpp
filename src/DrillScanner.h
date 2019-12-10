#ifndef DRILLSCANNER_H
#define DRILLSCANNER_H
#include "BitmapScanner.h"
#include "PointF.h"
#include <limits>
#include <cmath>

class DrillScanner {
private:
	bool IsJustInitialized = true;
	BitmapScanner drillBitmap;
	vector<PointF> holes;
	bool TryGetHole(int net, PointF & hole);
	void FindHoles();
public:
	DrillScanner(BitmapScanner & bitmapScanner);
	vector<PointF> GetHoles();
};
#endif