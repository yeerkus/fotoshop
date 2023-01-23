#ifndef CS221UTIL_RGBAPixel_H
#define CS221UTIL_RGBAPixel_H
#include <string>

namespace cs221util{
   class RGBAPixel {
        public: 
            RGBAPixel();
            RGBAPixel(int red, int green, int blue);
            RGBAPixel(int red, int green, int blue, double alpha);
        public:
            unsigned char r;
            unsigned char g;
            unsigned char b;
            double a;
    };
}

#endif