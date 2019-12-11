#ifndef LAYERNET_H
#define LAYERNET_H
#define TOPLAYER (0)
#define BOTTOMLAYER (1)
#define MAXLAYER (32)
#include <iostream>
#include <string>
using namespace std;

class LayerNet {
private:
	int layerId;
	int netId;
public:
	LayerNet(int layer, int net) : layerId(layer), netId(net) { }
	inline int getNetId() const { return netId; }
	inline void setNetId (int _netId) { netId = _netId; }
	inline int getLayerId() const { return layerId; }
	inline void setLayerId(int _layerId) { layerId = _layerId; }
	inline friend ostream& operator<<(ostream & os, const LayerNet & l) {
		return os << l.layerId << ":" << l.netId;
	}
//	inline bool operator<(const LayerNet & o) {
//		if (layerId < o.layerId) {
//			return true;
//		}
//		
//		if (layerId == o.layerId) {
//			return netId < o.netId;
//		}
//		return false;
//	}
	inline string tostring() {
		return to_string(layerId).append(":").append(to_string(netId));
	}
};

inline bool operator<(const LayerNet& l, const LayerNet& r) {
//	return l<r;
	if (l.getLayerId() < r.getLayerId()) {
		return true;
	}
	
	if (l.getLayerId() == r.getLayerId()) {
		return l.getNetId() < r.getNetId();
	}
	
	return false;
}
#endif
