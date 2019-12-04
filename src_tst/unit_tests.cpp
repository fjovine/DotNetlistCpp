#include "MockupBitmapAccessorTest.cpp"
#include "SegmentTests.cpp"

int main(int argc, char ** argv)
{
	MockupBitmapAccessorTest mockupMitmapAccessorTest;
	mockupMitmapAccessorTest.MockupBitmapAccessor_WorksWell_WithAllSet2x2bitmap();
	mockupMitmapAccessorTest.MockupBitmapAccessor_WorksWell_WithOneBitSet1x1bitmap();
	mockupMitmapAccessorTest.MockupBitmapAccessor_WorksWell_AlternatingFullAndVoidLines();
	
	SegmentTests segmentTests;
	segmentTests.Touches_WorksWell_InAllCases();
}