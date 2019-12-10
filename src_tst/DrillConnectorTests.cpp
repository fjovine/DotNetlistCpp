#include "../src/IBitmapAccessor.h"
#include "../src/DrillConnector.h"
class DrillConnectorTest {
private:
	IBitmapAccessor * top;
	IBitmapAccessor * bottom;
	IBitmapAccessor * drill;
	void CheckConnection(vector<string> & expected);
public:
	void ComputeGlobalNet_WorksWell_Case1();
	void ComputeGlobalNet_WorksWell_Case2();
};

void DrillConnectorTest::CheckConnection(vector<string> & expected) {
	BitmapScanner topLayer(top);
	topLayer.PrepareAll();

	BitmapScanner bottomLayer(bottom);
	bottomLayer.PrepareAll();

	BitmapScanner drillLayer(drill);
	drillLayer.PrepareAll();

	DrillScanner drillScanner(drillLayer);
	DrillConnector drillConnector(topLayer, bottomLayer, drillScanner);
	drillConnector.ComputeGlobalNet();
	auto nets = drillConnector.GetNets();
	int netCount = 0;
	for (int key : nets) 
	{
		cout << "KEY: " << key << endl;
		string sb;
		for (auto layerNet : drillConnector.GetLayerNetsOfNet(key)) {
			if (sb.size() > 0) {
				sb.append(",");
			}
			sb.append(layerNet.tostring());
		}
		cout << sb << endl;
		assert(expected[netCount] == sb);
		netCount ++;
	}
	cout << netCount << endl;
	assert(expected.size() == netCount);
}
void DrillConnectorTest::ComputeGlobalNet_WorksWell_Case1() {
	vector<string> top_bitmap {
	//   012345678
		"",
		"  XX  XX",
		"  XX  XX",
		"  XX  XX",
		"  XX  XX",
		"  XX  XX",
		"  XX  XX",
		""
	};
cout << "Case1.1" << endl;
	top = new MockupBitmapAccessor(top_bitmap);
	vector<string> bottom_bitmap {
	//   012345678
		"",
		"  XXXXXX",
		"  XXXXXX",
		"",
		"",
		"  XXXXXX",
		"  XXXXXX",
		""
	};
	bottom = new MockupBitmapAccessor(bottom_bitmap);
	vector<string> drill_bitmap {
	//   012345678
		"",
		"  XX  XX",
		"  XX  XX",
		"",
		"",
		"  XX  XX",
		"  XX  XX",
		""
	};
	drill = new MockupBitmapAccessor(drill_bitmap);
	vector<string> check = {
		"0:1,1:1,0:2,1:2"
	};
	CheckConnection(check);
	SHOWUNITTEST;
}
void DrillConnectorTest::ComputeGlobalNet_WorksWell_Case2() {
	SHOWUNITTEST;
}

