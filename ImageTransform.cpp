#include <iostream>
#include <cmath>
#include <cstdlib>

#include "uiuc/PNG.h"
#include "uiuc/HSLAPixel.h"
#include "ImageTransform.h"

/* ******************
(Begin multi-line comment...)

Write your name and email address in the comment space here:

Name:
Email:

(...end multi-line comment.)
******************** */

using uiuc::PNG;
using uiuc::HSLAPixel;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a reference to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly. No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 *
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {
     for (unsigned x = 0; x < image.width(); x++) {
         for (unsigned y = 0; y < image.height(); y++) {
            HSLAPixel & pixel = image.getPixel(x, y);
            int xdiff = abs(signed(x-centerX));
            int ydiff = abs(signed(y-centerY));
            double hyp = sqrt(xdiff*xdiff + ydiff*ydiff);
            if (hyp<=160.0){
            double dec = 0.5*hyp;
            pixel.l = pixel.l - (dec*pixel.l/100.0);
            }
            else{
            pixel.l = pixel.l - (80.0*pixel.l/100.0);
            }
         }
     }
            return image;
}




/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {
    int diffo,diffb;
     for (unsigned x = 0; x < image.width(); x++) {
         for (unsigned y = 0; y < image.height(); y++) {
             HSLAPixel & pixel = image.getPixel(x, y);
             if (pixel.h<=191){
                diffo = abs(pixel.h-11);
             }
                else{

                        diffo = 360 - pixel.h + 11;

                }
                if (pixel.h>=36){
                    diffb = abs(pixel.h-216);
                }
                else{
                    diffb = 360 - 216 + pixel.h;
                }
                if(diffo<=diffb){
                    pixel.h = 11;
                }
                else{
                    pixel.h = 216;
                }
             }
}


  return image;
}


/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs, which is the base image.
* @param secondImage The second of the two PNGs, which acts as the stencil.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {
    unsigned int height,width;
    for (unsigned x = 0; x < secondImage.width(); x++) {
         for (unsigned y = 0; y < secondImage.height(); y++) {
                HSLAPixel & pixela = firstImage.getPixel(x, y);
                HSLAPixel & pixelc = secondImage.getPixel(x, y);
                if (pixelc.l == 1.0){
                    pixela.l = pixela.l + 0.2;
                    if (pixela.l>1){
                        pixela.l = 1;
                    }
                }
         }
    }



  return firstImage;
}
