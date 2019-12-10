#define SHOWUNITTEST cout << "     " << __FUNCTION__ << " Ok" << endl
#include "MockupBitmapAccessorTest.cpp"
#include "SegmentTests.cpp"
#include "ScanlineTests.cpp"
#include "BitmapScannerTests.cpp"
#include "DrillScannerTest.cpp"
#include "LayerNetTest.cpp"
#include "DrillConnectorTests.cpp"

int main(int argc, char ** argv)
{
	cout << "MockupBitmapAccessorTest" << endl;
	MockupBitmapAccessorTest mockupMitmapAccessorTest;
	mockupMitmapAccessorTest.MockupBitmapAccessor_WorksWell_WithAllSet2x2bitmap();
	mockupMitmapAccessorTest.MockupBitmapAccessor_WorksWell_WithOneBitSet1x1bitmap();
	mockupMitmapAccessorTest.MockupBitmapAccessor_WorksWell_AlternatingFullAndVoidLines();
	
	cout << "SegmentTests" << endl;
	SegmentTests segmentTests;
	segmentTests.Touches_WorksWell_InAllCases();
	
	cout << "ScanlineTests" << endl;
	ScanlineTests scanlineTests;
	scanlineTests.Foreach_Works_Well();
	scanlineTests.GetTouchingSegment_Works_Well();
	scanlineTests.BackPropagate_Works_Well();

	cout << "BitmapScannerTests" << endl;
	BitmapScannerTests bitmapScannerTests;
	bitmapScannerTests.Scan_GeneratesGood_Scanlines();
	bitmapScannerTests.Scan_GeneratesGood_CompositeScanlnes_WorksWell();
	bitmapScannerTests.ComputeNetlists_WorksWell_Case1();
	bitmapScannerTests.ComputeNetlists_WorksWell_Case2();
	bitmapScannerTests.ComputeNetlists_WorksWell_Case3();
	bitmapScannerTests.MapNetlists_WorksWell();
	bitmapScannerTests.TryGetNetAt_WorksWell_WithProperInnput();

	cout << "DrillScannerTest" << endl;
	DrillScannerTest drillScannerTest;
	drillScannerTest.GetHoles_WorksWell_WithProperBitmap();

	cout << "LayerNetTest" << endl;
	LayerNetTest layerNetTest;
	layerNetTest.OperatorLessThan_Works_Well();
	
	cout << "DrillConnectorTest" << endl;
	DrillConnectorTest drillConnectorTest;
	drillConnectorTest.ComputeGlobalNet_WorksWell_Case1();
	drillConnectorTest.ComputeGlobalNet_WorksWell_Case2();
	cout << "UnitTests OK" << endl;
}