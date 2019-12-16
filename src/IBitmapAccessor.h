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
	inline int get_width() const { return width; }
	inline void set_width(int value) { width = value; }
	inline int get_height() const { return height; }
	inline void set_height(int value) { height = value; }
	virtual bool pixel_at(int x, int y)
	{
		cout << "IBitmapAccessor.1" << endl;
		throw invalid_argument("Unimplemented virtual method");
	}
};
#endif