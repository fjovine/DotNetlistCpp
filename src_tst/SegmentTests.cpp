#include "../src/Segment.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

class SegmentTests
{
	private:
		void Check(int Min, int Max, bool touches, string message);
	public:
		Segment segment = Segment(1,10,20);
		void Touches_WorksWell_InAllCases();
		SegmentTests();
};

void SegmentTests::Check(int Min, int Max, bool touches, string message) {
	Segment other(0,Min,Max);
	if (touches != segment.Touches(other)) {
		assert(false);
	}
}

void SegmentTests::Touches_WorksWell_InAllCases()
{
	Check(5, 5, false, "Case 1");
	Check(5, 10, true,"Case 2");
	Check(5, 11, true,"Case 3");
	Check(5, 20, true,"Case 4");
	Check(5, 21, true,"Case 5");
	Check(10,15, true,"Case 6");
	Check(11,15, true,"Case 7");
	Check(15, 20, true,"Case 8");
	Check(15, 21, true,"Case 9");
	Check(20, 21, true,"Case 10");
	Check(21, 30, false, "Case 11");
	SHOWUNITTEST;
}

SegmentTests::SegmentTests() {
}