#include "RGBAPixel.h"
#include <string>

namespace cs221util{
    RGBAPixel::RGBAPixel() {
        r = '255';
        g = '255';
        b = '255';
        a = 1.0;
    }

    RGBAPixel::RGBAPixel(int red, int green, int blue) {
        r = char(red);
        g = char(green);
        b = char(blue);
        a = 1.0;
    }

    RGBAPixel::RGBAPixel(int red, int green, int blue, double alpha) {
        r = char(red);
        g = char(green);
        b = char(blue);
        a = alpha;
    };
}