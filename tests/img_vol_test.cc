#include <iostream>
#include "img_vol.h"
#include "operations.h"
#include "img2d.h"

int main(int argc, char **argv) {
  ImgVol img("/home/alex/Downloads/libmc920/data/brain.scn");
  std::cout << img << "\n";

  std::cout << img(57, 9, 35) << "\n";

  Img2D img2dz = Cut(img, ImgVol::Axis::Z, 40);

  std::cout << img2dz << "\n";

  Img2D img2dy = Cut(img, ImgVol::Axis::Y, 40);

  std::cout << img2dy << "\n";

  Img2D img2dx = Cut(img, ImgVol::Axis::X, 40);

  std::cout << img2dx << "\n";
}
