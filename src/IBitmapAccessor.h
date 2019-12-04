#ifndef IBITMAPACCESSOR_H
#define IBITMAPACCESSOR_H
class IBitmapAccessor 
{
protected:
	int width;
	int height;
public:
	int get_width();
	int get_height();
	virtual bool pixel_at(int x, int y) {
		throw "Unimplemented virtual method";
	}
};
#endif