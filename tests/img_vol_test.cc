#include <iostream>
#include "img_vol.h"
#include "operations.h"
#include "img2d.h"

int main(int argc, char **argv) {
  ImgVol img("/home/alex/Downloads/libmo815-3dvis/data/brain.scn");
  std::cout << img << "\n";

  std::cout << img(57, 9, 35) << "\n";

  Img2D img2d = Cut(img, ImgVol::Axis::Z, 40);

  std::cout << img2d;
}
