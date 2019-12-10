#ifndef IBITMAPACCESSOR_H
#define IBITMAPACCESSOR_H
#include <iostream>

using namespace std;

class IBitmapAccessor 
{
protected:
	int width;
	int height;
public:
	int get_width();
	int get_height();
	virtual bool pixel_at(int x, int y)
	{
		cout << "IBitmapAccessor.1" << endl;
		throw invalid_argument("Unimplemented virtual method");
	}
};
#endif