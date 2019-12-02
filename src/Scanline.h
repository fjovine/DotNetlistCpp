#ifndef SCANLINE_H
#define SCANLINE_H
#include <functional>
using namespace std;

class Scanline
{
	private:
		int y;
		int initialIndex;
		int length;
	public:
		friend std::ostream& operator<<(std::ostream&, const Scanline&);
		void foreach(vector<Segment> segments,function<Segment> iterator);
}
#endif