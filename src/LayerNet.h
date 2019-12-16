#ifndef LAYERNET_H
#define LAYERNET_H
#define TOPLAYER (0)
#define BOTTOMLAYER (1)
#define MAXLAYER (32)
#include <iostream>
#include <string>
using namespace std;

/**
 /* Identifies the net on each layer.
 */
class LayerNet {
private:
	int layerId;
	int netId;
public:
	/**
	 * Initializes a new instance of the \ref "LayerNet" class.
	 * This class stores the couple layer identifier-net identifier of the layer.
	 * @param layer Layer where the local net is.
	 * @param net Net identifier of the local net.
	 */
	LayerNet(int layer, int net) : layerId(layer), netId(net) { }

	/**
	 * Gets or sets the net identifier.
	 */
	inline int getNetId() const { return netId; }
	inline void setNetId (int _netId) { netId = _netId; }

	/**
	 * Gets or sets the layer identifier.
	 */
	inline int getLayerId() const { return layerId; }
	inline void setLayerId(int _layerId) { layerId = _layerId; }

	/**
	 * Outputs on stout a readable version of an object of this class composed by
	 * the layerId, colum and the net id.
	 */
	inline friend ostream& operator<<(ostream & os, const LayerNet & l) {
		return os << l.layerId << ":" << l.netId;
	}

	/**
	 * Generates a readable version of an object of this class composed by
	 * the layerId, colum and the net id.
	 * @return A readable version of an object of this class.
	 */
	inline string tostring() {
		return to_string(layerId).append(":").append(to_string(netId));
	}
};

/**
 * The couple layer:net is a totally ordered set.
 * This function compare the passed parameter and returns true if l is less than r.
 * If the layer Id's differ, it is less the couple having the smaller layer Id.
 * If the layer Id's are equal, it is less the couple having the smaller net id.
 * @param LayerNet to the left of the less-than sign
 * @param LayerNet to the right of the less-than sign.
 * @return true if l<r with the total ordering defined for this class.
 */
inline bool operator<(const LayerNet& l, const LayerNet& r) {
	if (l.getLayerId() < r.getLayerId()) {
		return true;
	}
	
	if (l.getLayerId() == r.getLayerId()) {
		return l.getNetId() < r.getNetId();
	}
	
	return false;
}
#endif
