#include "operations.h"

Img2D Cut(const ImgVol& img_vol, ImgVol::Axis axis, size_t pos, int graus) {

  Img2D img2d(img_vol.SizeX(), img_vol.SizeY());

  for (int i = 0; i < img_vol.SizeX(); i++) {
    for (int j = 0; j < img_vol.SizeY(); j++) {
      img2d(img_vol(i, j, pos), i, j);
    }
  }

  return img2d;
}
