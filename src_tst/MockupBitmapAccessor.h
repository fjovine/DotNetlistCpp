#ifndef MOCKUPBITMAPACCESSOR_H
#define MOCKUPBITMAPACCESSOR_H
#include "../src/IBitmapAccessor.h"
#include <string>
#include <vector>
using namespace std;
class MockupBitmapAccessor : public IBitmapAccessor
{
private:
	vector<string> the_bitmap;
public:
	bool pixel_at(int x, int y);
	MockupBitmapAccessor(vector<string> bitmap);
};
#endif