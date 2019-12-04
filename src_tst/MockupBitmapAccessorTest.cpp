#include "MockupBitmapAccessor.h"
#include <cassert>
#include <iostream>

using namespace std;

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
	cout << __FUNCTION__ << " Ok" << endl;
}

void MockupBitmapAccessorTest::MockupBitmapAccessor_WorksWell_WithOneBitSet1x1bitmap()
{
	vector<string> test_bitmap {
		"X"
	};
	
	IBitmapAccessor *accessor = new MockupBitmapAccessor(test_bitmap);
	AssertAllSet(1,1, accessor);
	cout << __FUNCTION__ << " Ok" << endl;
}

void MockupBitmapAccessorTest::MockupBitmapAccessor_WorksWell_AlternatingFullAndVoidLines()
{
	vector<string> test_bitmap {
		"XXXXXX",
		"",
		"XXXXXX",
		"",
	};

	IBitmapAccessor *accessor = new MockupBitmapAccessor(test_bitmap);	
	assert(6 == accessor->get_width());
	assert(4 == accessor->get_height());
	for (int x = 0; x < accessor->get_width(); x++) 
	{
		for (int y=0; y<accessor->get_height(); y++)
		{
			if (y%2 ==1)
			{
				assert(!accessor->pixel_at(x,y));
			}
			else
			{
				assert(accessor->pixel_at(x,y));
			}
		}
	}
	cout << __FUNCTION__ << " Ok" << endl;
}

