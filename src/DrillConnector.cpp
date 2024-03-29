#include "DrillConnector.h"

bool DrillConnector::LayerNet2NetContainsKey(LayerNet & layerNet) {
	return layerNet2net.find(layerNet) != layerNet2net.end();
}

void DrillConnector::ComputeGlobalNet() {
	int globalNet = 1;
	for (auto hole: drill.GetHoles()) {
		LayerNet * topNet = NULL;
		LayerNet * bottomNet = NULL;
		int topId = 0;
		
		if (top.TryGetNetAt(hole.X, hole.Y, topId)) {
			topNet = new LayerNet(TOPLAYER, topId);
		}
		
		int bottomId = 0;
		if (bottom.TryGetNetAt(hole.X, hole.Y, bottomId)) {
			bottomNet = new LayerNet(BOTTOMLAYER, bottomId);
		}

		bool topNetAlreadyConnected = (topNet != NULL) && LayerNet2NetContainsKey(*topNet);
		bool bottomNetAlreadyConnected = (bottomNet != NULL) && LayerNet2NetContainsKey(*bottomNet);

		if (!topNetAlreadyConnected && !bottomNetAlreadyConnected) {
			// The nets are not connected. A new global net is created.
			vector<LayerNet> v;
			net2connectedLayerNets[globalNet] = v;
			if (topNet != NULL)
			{
				net2connectedLayerNets[globalNet].push_back(*topNet);
				layerNet2net[*topNet] = globalNet;
			}

			if (bottomNet != NULL)
			{
				net2connectedLayerNets[globalNet].push_back(*bottomNet);
				layerNet2net[*bottomNet] = globalNet;
			}
			globalNet++;
			continue;
		}
		
		if (topNetAlreadyConnected && !bottomNetAlreadyConnected)
		{
			int unify = layerNet2net[*topNet];
			layerNet2net[*bottomNet] = unify;
			net2connectedLayerNets[unify].push_back(*bottomNet);
			continue;
		}

		if (bottomNetAlreadyConnected && !topNetAlreadyConnected)
		{
			int unify = layerNet2net[*bottomNet];
			layerNet2net[*topNet] = unify;
			net2connectedLayerNets[unify].push_back(*topNet);
			continue;
		}

		if (topNetAlreadyConnected && bottomNetAlreadyConnected)
		{
			// If both are connected, we reduce to the top layer.
			int unify = layerNet2net[*topNet];
			int localBottomNet = layerNet2net[*bottomNet];
			if (unify == localBottomNet)
			{
				continue;
			}

			auto bottomList = net2connectedLayerNets[localBottomNet];
			for (auto bottomElement : bottomList) {
				net2connectedLayerNets[unify].push_back(bottomElement);
			}			
			net2connectedLayerNets.erase(localBottomNet);
			for (auto localnet : bottomList)
			{
				layerNet2net[localnet] = unify;
			}
		}
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