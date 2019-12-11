#include "DrillConnector.h"

bool DrillConnector::LayerNet2NetContainsKey(LayerNet & layerNet) {
	return layerNet2net.find(layerNet) != layerNet2net.end();
}

void DrillConnector::ComputeGlobalNet() {
	cout << "Entering ComputeGlobalNet" << endl;
	int globalNet = 1;
	for (auto hole: drill.GetHoles()) {
		cout << "Hole " << hole << endl;
		LayerNet * topNet = NULL;
		LayerNet * bottomNet = NULL;
		int topId = 0;
		
		if (top.TryGetNetAt(hole.X, hole.Y, topId)) {
			topNet = new LayerNet(TOPLAYER, topId);
		}
cout << "Top Net id : " << topId << " - " << *topNet << endl;
		
		int bottomId = 0;
		if (bottom.TryGetNetAt(hole.X, hole.Y, bottomId)) {
			bottomNet = new LayerNet(BOTTOMLAYER, bottomId);
		}
cout << "Bot Net id : " << bottomId << " - " << *bottomNet << endl;

		bool topNetAlreadyConnected = (topNet != NULL) && LayerNet2NetContainsKey(*topNet);
		bool bottomNetAlreadyConnected = (bottomNet != NULL) && LayerNet2NetContainsKey(*bottomNet);

cout << "Topnet already connected : " << topNetAlreadyConnected << endl;
cout << "Bottomnet already connnected : " << bottomNetAlreadyConnected << endl;
cout << "layerNet2net size : " << layerNet2net.size() << endl;
		for (auto pair : layerNet2net) {
			cout << "{" << pair.first << "} {" << pair.second << "}" << endl;
		}
		
cout << "ComputeGlobalNet.1" << endl;
		if (!topNetAlreadyConnected && !bottomNetAlreadyConnected) {
			// The nets are not connected. A new global net is created.
cout << "ComputeGlobalNet.1.1" << endl;
			vector<LayerNet> v;
cout << "ComputeGlobalNet.1.2" << endl;
			net2connectedLayerNets[globalNet] = v;
cout << "ComputeGlobalNet.1.3" << endl;
			if (topNet != NULL)
			{
cout << "ComputeGlobalNet.1.3.1" << endl;
				net2connectedLayerNets[globalNet].push_back(*topNet);
cout << "ComputeGlobalNet.1.3.2" << endl;
				layerNet2net[*topNet] = globalNet;
cout << "ComputeGlobalNet.1.3.3" << endl;
			}
cout << "ComputeGlobalNet.1.3.4" << endl;

			if (bottomNet != NULL)
			{
cout << "ComputeGlobalNet.1.3.5 bottomNet " << *bottomNet << endl;
				net2connectedLayerNets[globalNet].push_back(*bottomNet);
cout << "ComputeGlobalNet.1.3.6 layerNet2net globalNet " << globalNet << endl;
cout << "layerNet2net size : " << layerNet2net.size() << endl;
		for (auto pair : layerNet2net) {
			cout << "{" << pair.first << "} {" << pair.second << "}" << endl;
		}
				layerNet2net[*bottomNet] = globalNet;
cout << "ComputeGlobalNet.1.3.7" << endl;
			}
cout << "ComputeGlobalNet.1.3.8" << endl;
			globalNet++;
			continue;
		}
		
cout << "ComputeGlobalNet.2" << endl;
		if (topNetAlreadyConnected && !bottomNetAlreadyConnected)
		{
			int unify = layerNet2net[*topNet];
			layerNet2net[*bottomNet] = unify;
			net2connectedLayerNets[unify].push_back(*bottomNet);
			continue;
		}

cout << "ComputeGlobalNet.3" << endl;
		if (bottomNetAlreadyConnected && !topNetAlreadyConnected)
		{
			int unify = layerNet2net[*bottomNet];
			layerNet2net[*topNet] = unify;
			net2connectedLayerNets[unify].push_back(*topNet);
			continue;
		}

cout << "ComputeGlobalNet.4" << endl;
		if (topNetAlreadyConnected && bottomNetAlreadyConnected)
		{
cout << "ComputeGlobalNet.4.0" << endl;
			// If both are connected, we reduce to the top layer.
			int unify = layerNet2net[*topNet];
cout << "ComputeGlobalNet.4.0.1" << endl;
			int localBottomNet = layerNet2net[*bottomNet];
cout << "ComputeGlobalNet.4.0.2" << endl;
			if (unify == localBottomNet)
			{
cout << "ComputeGlobalNet.4.0.3" << endl;
				continue;
			}

cout << "ComputeGlobalNet.4.1" << endl;
			auto bottomList = net2connectedLayerNets[localBottomNet];
			for (auto bottomElement : bottomList) {
cout << "ComputeGlobalNet.4.2" << endl;
				net2connectedLayerNets[unify].push_back(bottomElement);
			}			
			net2connectedLayerNets.erase(localBottomNet);
			for (auto localnet : bottomList)
			{
cout << "ComputeGlobalNet.4.3" << endl;
				layerNet2net[localnet] = unify;
			}
		}
		cout << "Exit ComputeGlobalNet" << endl;
	}
}

vector<LayerNet> DrillConnector::GetLayerNetsOfNet(int net) {
	return net2connectedLayerNets[net];
}

vector<int> DrillConnector::GetNets() {
	vector<int> result;
	for (auto pair : net2connectedLayerNets) {
		result.push_back(pair.first);
	}
	return result;
}