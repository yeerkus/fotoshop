#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "lab_intro.h"

using namespace cs221util;

PNG grayscale(PNG image) {
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      RGBAPixel* pixel = image.getPixel(x, y);

      double grayvalue = 0.0;
      double adjusted_red = 0.229 * pixel->r;
      double adjusted_green = 0.587 * pixel->g;
      double adjusted_blue = 0.114* pixel->b;

      grayvalue = adjusted_red + adjusted_green + adjusted_blue;
      
      pixel->r = (unsigned char) grayvalue;
      pixel->g = (unsigned char) grayvalue;
      pixel->b = (unsigned char) grayvalue;
    }
  }

  return image;
}

PNG createSpotlight(PNG image, int centerX, int centerY) {
  for(unsigned x = 0; x < image.width(); x++) {
    for(unsigned y = 0; y < image.height(); y++) {
      float distance = sqrt((x-centerX)*(x-centerX) + (y-centerY)*(y-centerY));
      RGBAPixel* pixel = image.getPixel(x,y);
      if(distance > 200.0) {
        pixel->r = (unsigned char) 0;
        pixel->g = (unsigned char) 0;
        pixel->b = (unsigned char) 0;
      } else {
        pixel->r = (unsigned char) (pixel->r-(distance*0.005)*pixel->r);
        pixel->g = (unsigned char) (pixel->g-(distance*0.005)*pixel->g);
        pixel->b = (unsigned char) (pixel->b-(distance*0.005)*pixel->b);
      }
    }
  }

  return image;
}

PNG ubcify(PNG image) {
  RGBAPixel* ubc_blue = new RGBAPixel(12, 35, 68, 1);
  RGBAPixel* ubc_yellow = new RGBAPixel(255, 255, 0, 1);
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      RGBAPixel* pixel = image.getPixel(x,y);
      float blueDistance = colordist(*pixel, *ubc_blue);
      float yellowDistance = colordist(*pixel, *ubc_yellow);
      if (blueDistance > yellowDistance) {
        pixel->r = ubc_blue->r;
        pixel->g = ubc_blue->g;
        pixel->b = ubc_blue->b;
      } else {
        pixel->r = ubc_yellow->r;
        pixel->g = ubc_yellow->g;
        pixel->b = ubc_yellow->b;
      }
    }
  }
  return image;
}

PNG watermark(PNG firstImage, PNG secondImage) {
  for(unsigned x = 0; x < firstImage.width(); x++) {
    for(unsigned y = 0; y < firstImage.height(); y++) {
      RGBAPixel* pixel = secondImage.getPixel(x,y);
      RGBAPixel* pixel1 = firstImage.getPixel(x,y);
      if(pixel->a == 1 && pixel->b == (unsigned char) 255 && pixel->g == (unsigned char) 255 && pixel->r == (unsigned char) 255) {
        pixel1->r + 40 > 255 ? pixel1->r = 255 : pixel1->r += 40;
        pixel1->g + 40 > 255 ? pixel1->g = 255 : pixel1->g += 40;
        pixel1->g + 40 > 255 ? pixel1->g = 255 : pixel1->g += 40;
      }
    }
  }
  return firstImage;
}

double colordist(RGBAPixel px1, RGBAPixel px2) {
  // scale each channel to [0,1] range and pre-multiply alpha
  double dbl_r_px1 = (double)px1.r / 255.0 * px1.a;
  double dbl_r_px2 = (double)px2.r / 255.0 * px2.a;
  double dbl_g_px1 = (double)px1.g / 255.0 * px1.a;
  double dbl_g_px2 = (double)px2.g / 255.0 * px2.a;
  double dbl_b_px1 = (double)px1.b / 255.0 * px1.a;
  double dbl_b_px2 = (double)px2.b / 255.0 * px2.a;

  double delta_a = px1.a - px2.a;

  // compute maximum of each channel blended on white, and blended on black
  // red channel
  double black = dbl_r_px1 - dbl_r_px2;
  double white = black + delta_a;
  double diff_r = max(black * black, white * white);
  // green channel
  black = dbl_g_px1 - dbl_g_px2;
  white = black + delta_a;
  double diff_g = max(black * black, white * white);
  // blue channel
  black = dbl_b_px1 - dbl_b_px2;
  white = black + delta_a;
  double diff_b = max(black * black, white * white);

  return diff_r + diff_g + diff_b;
}
