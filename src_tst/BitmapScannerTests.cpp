#include "../src/BitmapScanner.h"
#include <cassert>
using namespace std;

class BitmapScannerTests {
private:
	bool IsSingleNetlist(BitmapScanner & dut);
public:
	void Scan_GeneratesGood_Scanlines();
	void Scan_GeneratesGood_CompositeScanlnes_WorksWell();
	void ComputeNetlists_WorksWell_Case1();
	void ComputeNetlists_WorksWell_Case2();
	void ComputeNetlists_WorksWell_Case3();
	void MapNetlists_WorksWell();
	void TryGetNetAt_WorksWell_WithProperInnput();
};

void BitmapScannerTests::Scan_GeneratesGood_Scanlines() {
	vector<string> test_bitmap {
	//   012345678
		"XXXXXXXXX",
		" XXXXXXX",
		"  XXXXX",
		"   XXX",
		"    X",
		""
	};
	
	int expectedStart[] = { 0, 1, 2, 3, 4 };
	int expectedEnd[] = { 8,7,6,5,4 };
	
	MockupBitmapAccessor accessor = MockupBitmapAccessor(test_bitmap);
	BitmapScanner dut (&accessor);
	dut.Scan();
	auto segments = dut.GetSegments();
	int y = 0;
	for (auto i : segments) {
		assert(expectedStart[y] == i.getXMin());
		assert(expectedEnd[y] == i.getXMax());
		y++;
	}

	SHOWUNITTEST;
}

void BitmapScannerTests::Scan_GeneratesGood_CompositeScanlnes_WorksWell() {
	vector<string> test_bitmap {
	//   012345678
		"  XXXXX",
		" XX    X",
		" XX XXX X",
		"",
		" XX XXX X",
		"  XX    X",
		"   XXXX",
		"" };
	
	int expectedy[] { 0,1,1,2,2,2,4,4,4,5,5,6 };
	int expectedStart[] { 2,1,7,1,4,8,1,4,8,2,8,3 };
	int expectedEnd[] { 6,2,7,2,6,8,2,6,8,3,8,6 };
	MockupBitmapAccessor accessor = MockupBitmapAccessor(test_bitmap);	
	BitmapScanner dut (&accessor);
	dut.Scan();
	auto segments = dut.GetSegments();
	int y = 0;
	for (auto s : segments) {
		assert(expectedy[y] == s.getY());
		assert(expectedStart[y] == s.getXMin());
		assert(expectedEnd[y] == s.getXMax());
		y++;
	}
	
	// Check scanline index
	int expectedY[] { 0,1,2,4,5,6 };
	int expectedInitial[] { 0, 1, 3, 6, 9, 11 };
	int expectedLen[] { 1,2,3,3,2, 1};

	auto i = 0;
	for (auto index : dut.GetScanlineIndex()) 
	{
		assert(expectedY[i] == index.getY());
		assert(expectedInitial[i] == index.getInitialIndex());
		assert(expectedLen[i] == index.getLength());
		i++;
	}
	assert(i == sizeof(expectedY)/sizeof(expectedY[0]));
	
	SHOWUNITTEST;
}

void BitmapScannerTests::ComputeNetlists_WorksWell_Case1() {
	vector<string> test_bitmap {
	//   012345678
		"X       X",
		"X       X",
		"X       X",
		"X       X",
		"XXXXXXXXX",
		"",
	};
	MockupBitmapAccessor accessor = MockupBitmapAccessor(test_bitmap);
	BitmapScanner dut (&accessor);
	assert(IsSingleNetlist(dut));
	SHOWUNITTEST;
}

void BitmapScannerTests::ComputeNetlists_WorksWell_Case2() {
	vector<string> test_bitmap {
		"  XXXX       XXXXXXXX            X",
		" XXXXXX     XXXX   XXXXX       XXX",
		"XXXXXXXXXXXXXX       XXXXX  XXXX",
		"                        XXXXX"
	};
	
	MockupBitmapAccessor accessor = MockupBitmapAccessor(test_bitmap);
	BitmapScanner dut (&accessor);
	assert(IsSingleNetlist(dut));
	SHOWUNITTEST;
}

void BitmapScannerTests::ComputeNetlists_WorksWell_Case3() {
	vector<string> test_bitmap {
	//   012345678
		"X       X",
		" X       X",
		"X       X",
		" X       X",
		"XXXXXXXXX",
		"",
	};
	
	MockupBitmapAccessor accessor = MockupBitmapAccessor(test_bitmap);
	BitmapScanner dut (&accessor);
	assert(!IsSingleNetlist(dut));
	SHOWUNITTEST;
}

void BitmapScannerTests::MapNetlists_WorksWell() {
	vector<string> test_bitmap {
	//   012345678
		"X        X",
		"X  X  X  X",
		"X  X  X  X",
		"XXXX  XXXX",
		"",
	};
	MockupBitmapAccessor accessor = MockupBitmapAccessor(test_bitmap);
	BitmapScanner dut (&accessor);
	dut.Scan();
	dut.ComputeNetlists();
	dut.CompactNets();
	dut.MapNetlists();
	
	int expected_y[] = { 0,1,1,2,2,3 };
	int expected_x_net1[] = { 0,0,3,0,3,0 };
	int expected_X_net1[] = { 0,0,3,0,3,3 };
	int expected_x_net2[] = { 9,6,9,6,9,6 };
	int expected_X_net2[] = { 9,6,9,6,9,9 };
	assert(2 == dut.GetNetCount());
	int i = 0;
	for (auto segment : dut.GetSegmentsOfNet(1)) {
		assert(segment.getY() == expected_y[i]);
		assert(segment.getXMin() == expected_x_net1[i]);
		assert(segment.getXMax() == expected_X_net1[i]);
		i++;
	}
	i = 0;
	for (auto segment : dut.GetSegmentsOfNet(2)) {
		assert(segment.getY() == expected_y[i]);
		assert(segment.getXMin() == expected_x_net2[i]);
		assert(segment.getXMax() == expected_X_net2[i]);
		i++;
	}
	
	SHOWUNITTEST;
}

void BitmapScannerTests::TryGetNetAt_WorksWell_WithProperInnput() {
	vector<string> test_bitmap {
	//   012345678
		"  XXXXXXX",
		" XX     X",
		" XX XXX X",
		"",
		" XX XXX X",
		"  XX    X",
		"   XXXX",
		"",
	};
	//   012345678
	//	"  1111111", //0
	//	" 11     1", //1
	//	" 11 222 1", //2
	//	"",          //3
	//	" 33 444 5", //4
	//	"  33    5", //5
	//	"   3333",   //6
	//	"",
	MockupBitmapAccessor accessor = MockupBitmapAccessor(test_bitmap);
	BitmapScanner dut (&accessor);
	dut.Scan();
	dut.ComputeNetlists();
	dut.CompactNets();
	dut.MapNetlists();
	int netId = 0;
	
	assert(dut.TryGetNetAt(1,2, netId));
	assert(netId == 1);
	assert(dut.TryGetNetAt(5,2, netId));
	assert(netId == 2);
	assert(dut.TryGetNetAt(5,4, netId));
	assert(netId == 4);
	assert(dut.TryGetNetAt(3,4, netId)==false);
	
	SHOWUNITTEST;	
}

bool BitmapScannerTests::IsSingleNetlist(BitmapScanner & dut) {
	bool result = true;
	dut.Scan();
	dut.ComputeNetlists();
	for (auto segment : dut.GetSegments()) 
	{
		result &= segment.getNetList() == 1;
	}

	return result;	
}
