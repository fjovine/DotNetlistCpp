#include "MockupBitmapAccessor.h"

bool MockupBitmapAccessor::pixel_at(int x, int y)
{
	if ((x>=width) || (y>=height)) 
	{
		throw "Invalid bit coordinates";
	}

	string scanline = the_bitmap[y];
	if (x>=scanline.length()) 
	{
		return false;
	}
	
	return scanline[x]=='X';
}

MockupBitmapAccessor::MockupBitmapAccessor(vector<string> bitmap)
{
	the_bitmap = bitmap;
	int max_string_length = 0;
	int line_count = 0;
	for (string line : bitmap) {
		if (line.length() > max_string_length) {
			max_string_length = line.length();
		}
		line_count ++;
	}
	
	width = max_string_length;
	height = line_count;
}