#include "operations.h"

namespace imgvol {

Img2D Cut(const ImgVol& img_vol, ImgVol::Axis axis, size_t pos) {
  size_t s1, s2;

  if (axis == ImgVol::Axis::Z) {
    s1 = img_vol.SizeX();
    s2 = img_vol.SizeY();
  } else if (axis == ImgVol::Axis::X) {
    s1 = img_vol.SizeZ();
    s2 = img_vol.SizeY();
  } else {
    s1 = img_vol.SizeZ();
    s2 = img_vol.SizeX();
  }

  Img2D img2d(s1, s2);

  for (int i = 0; i < s1; i++) {
    for (int j = 0; j < s2; j++) {
      if (axis == ImgVol::Axis::Z) {
        img2d(img_vol(i, j, pos), i, j);
      } else if (axis == ImgVol::Axis::X) {
        img2d(img_vol(pos, j, i), i, j);
      } else {
        img2d(img_vol(j, pos, i), i, j);
      }
    }
  }

  return img2d;
}

}
