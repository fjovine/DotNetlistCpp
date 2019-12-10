#include "../src/Scanline.h"
#include "../src/BitmapScanner.h"
#include "MockupBitmapAccessor.h"
using namespace std;

class ScanlineTests
{
	private:
		void AssertSegmentsAreEqual(int _y, int _x, int _X, Segment & sement);
	public:
		void Foreach_Works_Well();
		void GetTouchingSegment_Works_Well();
		void BackPropagate_Works_Well();
};

void ScanlineTests::AssertSegmentsAreEqual(int _y, int _x, int _X, Segment & segment)
{
	assert(_y == segment.getY());
	assert(_x == segment.getXMin());
	assert(_X == segment.getXMax());
}

void ScanlineTests::Foreach_Works_Well()
{
	vector<string> test_bitmap {
	//   012345678
		"XX XX XXX"
	};
	int segmentNo;;
	MockupBitmapAccessor accessor = MockupBitmapAccessor(test_bitmap);
	BitmapScanner scanner(& accessor);
	scanner.Scan();
	Scanline dut = scanner.GetScanlineIndex()[0];
	auto segments = scanner.GetSegments();
	segmentNo = 0;
	dut.Foreach(
		segments,
		[&segmentNo, this](Segment & segment) {			
			switch (segmentNo) {
			case 0: AssertSegmentsAreEqual(0,0,1, segment); break;
			case 1: AssertSegmentsAreEqual(0,3,4, segment); break;
			case 2: AssertSegmentsAreEqual(0,6,8, segment); break;
			}
			segmentNo++;
		}
	);
	SHOWUNITTEST;
}

void ScanlineTests::GetTouchingSegment_Works_Well()
{
	vector<string> test_bitmap {
	//             111111111122222222223333333333
	//   0123456789012345678901234567890123456789
		"XX XX XXXXXXX XX XXXX XXXXX XXXXX X XXXX",
		"        XXXXXXXXXXXXXXXXXXXXXX"
	};
	
	MockupBitmapAccessor accessor = MockupBitmapAccessor(test_bitmap);
	BitmapScanner scanner(& accessor);
	scanner.Scan();
	auto segments = scanner.GetSegments();
	auto lastSegment = segments[segments.size()-1];
	auto lastScanline = scanner.GetScanlineIndex()[0];
	auto touching = lastScanline.GetTouchingSegments(segments, lastSegment);
	assert(5 == touching.size());
	AssertSegmentsAreEqual(0,6,12, touching[0]);
	AssertSegmentsAreEqual(0,14,15, touching[1]);
	AssertSegmentsAreEqual(0,17,20, touching[2]);
	AssertSegmentsAreEqual(0,22,26, touching[3]);
	AssertSegmentsAreEqual(0,28,32, touching[4]);	
	SHOWUNITTEST;
}

void ScanlineTests::BackPropagate_Works_Well()
{
	vector<string> test_bitmap {
	//             111111111122222222223333333333
	//   0123456789012345678901234567890123456789
		"XX XX XXXXXXX XX XXXX XXXXX XXXXX X XXXX",
		"        XXXXXXXXXXXXXXXXXXXXXX",
		"XX XX XXXXXXX XX XXXX XXXXX XXXXX X XXXX"
	};
	MockupBitmapAccessor accessor = MockupBitmapAccessor(test_bitmap);
	BitmapScanner scanner(& accessor);
	scanner.Scan();	
	auto segments = scanner.GetSegments();
	for (int i=0;i<segments.size(); i++) {
		auto segment = segments[i];
		segment.setNetList(1);
		segments[i] = segment;
	}
	auto scanline = scanner.GetScanlineIndex()[1];
	scanline.BackPropagate(segments, 2,1);

	for (auto segment : segments)
	{
		if (segment.getY() <= 1) {
			assert(2 == segment.getNetList());
		}
		else
		{
			assert(1 == segment.getNetList());
		}
	}	
	SHOWUNITTEST;
}

