#include "../src/LayerNet.h"
#include <iostream>
#include <cassert>

class LayerNetTest {
public:
	void OperatorLessThan_Works_Well();
};

void LayerNetTest::OperatorLessThan_Works_Well()
{
	LayerNet l1(1,1);
	LayerNet l2(1,2);
	LayerNet l3(2,1);

	assert(l1 < l2);
	assert(l2 < l3);
	assert(!(l2 < l2));
	SHOWUNITTEST;
}