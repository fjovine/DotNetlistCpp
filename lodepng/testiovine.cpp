#include "lodepng.h"
#include <iostream>

using namespace std;

void set_pixel(vector<unsigned char> &image, int x, int y, int width, int height)
{
    for (int i=0; i<4; i++) {
        image[4 * width * y + 4 * x + i] = 0x88;
    }
}


vector<unsigned char> image;

int main(int argc, char *argv[]) {
    unsigned width, height;

    unsigned error = lodepng::decode(image, width, height, "CS019bottom.png");

    if (error) cout << "decoder error " << error << ": " << lodepng_error_text(error) << endl;
	cout << "W " << width << " H " << height << endl;

    for(unsigned y = 0; y < 300; y++) {
        set_pixel(image, y, y, width, height);
    } 
    error = lodepng::encode("out.png", image, width, height);

    if (error) cout << "decoder error " << error << ": " << lodepng_error_text(error) << endl;
    return 0;
}

