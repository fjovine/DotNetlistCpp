#include <vector>
#include "IBitmapAccessor.h"
#include "Segment.h"
#include "Scanline.h"

class BitmapScanner {
private:
	IBitmapAccessor bitmap;
	vector<Segment> segments;
	vector<Scanline> scanlines;