#ifndef DRILLCONNECTOR_H
#define DRILLCONNECTOR_H
#include <map>
#include <vector>
#include "BitmapScanner.h"
#include "DrillScanner.h"
#include "LayerNet.h"

using namespace std;
class DrillConnector {
private:
	BitmapScanner top;
	BitmapScanner bottom;
	DrillScanner drill;
	map<LayerNet, int> layerNet2net;
	map<int, vector<LayerNet>> net2connectedLayerNets;
	bool LayerNet2NetContainsKey(LayerNet & layerNet);
public:
	DrillConnector(BitmapScanner &_top, BitmapScanner &_bottom, DrillScanner &_drill) : top(_top), bottom(_bottom), drill(_drill) {}
	vector<int> GetNets();
	vector<LayerNet> GetLayerNetsOfNet(int net);
	void ComputeGlobalNet();
};
#endif