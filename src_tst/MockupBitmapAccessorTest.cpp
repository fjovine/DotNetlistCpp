#include "MockupBitmapAccessor.h"
#include <cassert>

class MockupBitmapAccessorTest
{
private:
	void AssertAllSet(int width, int height, IBitmapAccessor * accessor);
public:
        void MockupBitmapAccessor_WorksWell_WithAllSet2x2bitmap();
        void MockupBitmapAccessor_WorksWell_WithOneBitSet1x1bitmap();
        void MockupBitmapAccessor_WorksWell_AlternatingFullAndVoidLines();
	MockupBitmapAccessorTest();
};


MockupBitmapAccessorTest::MockupBitmapAccessorTest()
{
}

void MockupBitmapAccessorTest::AssertAllSet(int width, int height, IBitmapAccessor * accessor)
{
	assert(width == accessor->get_width());
	assert(height == accessor->get_height());
	for (int x = 0; x < width; x++) {
		for (int y=0; y<height; y++){
			assert(accessor->pixel_at(x,y));
		}
	}	
}

void MockupBitmapAccessorTest::MockupBitmapAccessor_WorksWell_WithAllSet2x2bitmap()
{
	vector<string> test_bitmap {
		"XX",
		"XX"
	};
	
	IBitmapAccessor * accessor = new MockupBitmapAccessor(test_bitmap);
	AssertAllSet(2,2, accessor);
}

int main(int argc, char ** argv)
{
	MockupBitmapAccessorTest test;
	test.MockupBitmapAccessor_WorksWell_WithAllSet2x2bitmap();
}