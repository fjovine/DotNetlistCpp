#ifndef DRILLCONNECTOR_H
#define DRILLCONNECTOR_H
#include <map>
#include <vector>
#include "BitmapScanner.h"
#include "DrillScanner.h"
#include "LayerNet.h"

using namespace std;
/**
 * Starting from the top and bottom layer, using the passed drill layer
 * computes the connection between the nets of the top and the bottom layer.
 */
class DrillConnector {
private:
	/**
	 *  Scanner of the top layer.
	 */
	BitmapScanner top;

	/**
	 * Scanner of the bottom layer.
	 */
	BitmapScanner bottom;

	/**
	 * Scanner of the drill layer.
	 */
	DrillScanner drill;

	/**
	 * Maps the identifier of nets on each layer to the global net identifier.
	 */
	map<LayerNet, int> layerNet2net;

	/**
	 * Maps the global net to the local nets of each layer.
	 */
	map<int, vector<LayerNet>> net2connectedLayerNets;

	/**
	 * Determines if the \ref layerNet2Net map contains the passed
	 * \see LayerNet as a key.
	 * @param layerNet Layer-net couple to be looked for.
	 * @return true if the passed key is a key in the \ref layerNet2Net map.
	 */
	bool LayerNet2NetContainsKey(LayerNet & layerNet);
public:
	/**
	 * Initializes a new instance of the \see DrillConnector class.
	 * This class builds the connection between nets on the top and bottom layers of the PCB by means
	 * of the drills layer.
	 * @param top BitmapScanner of the top layer.
	 * @param bottom BitmapScanner of the bottom layer layer.
	 * @param drill DrillScanner of the drill layer.
	 */
	DrillConnector(BitmapScanner &_top, BitmapScanner &_bottom, DrillScanner &_drill) : top(_top), bottom(_bottom), drill(_drill) {}

	/**
	 * Computes the enumeration of defined local nets.
	 * @return A vector containing theh defined local nets.
	 */
	vector<int> GetNets();

	/**
	 * Computes the list of local nets (i.e. nets on top and bottom layers) corresponding to the passed
	 * global net.
	 * @param net Global net identifier.
	 * @return The enumeration of \see "LayerNet" that reference each net on both layers that are connected.
	 */
	vector<LayerNet> GetLayerNetsOfNet(int net);

	/**
	 * This method computes the global nets of the PCB considering that nets of the top and bottom layers are
	 * indeed connected, i.e. just one, when they touch a hole.
	 * The correspondence between the nets on top and bottom layers is stored in the 
	 * \see "layerNet2net" and \see "net2connectedLayerNets" dictionaries.
	 */
	void ComputeGlobalNet();
};
#endif