class IBitmapAccessor 
{
protected:
	int width;
	int height;
public:
	int get_width();
	int get_height();
	virtual bool pixel_at(int x, int y) = 0;
};