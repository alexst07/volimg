#include <iostream>
#include "img_vol.h"
#include "operations.h"
#include "img2d.h"

int main(int argc, char **argv) {
  imgvol::ImgVol img("/home/alex/Downloads/libmc920/data/brain.scn");
  std::cout << img << "\n";

  std::cout << img(57, 9, 35) << "\n";

  imgvol::Img2D img2dz = imgvol::Cut(img, imgvol::ImgVol::Axis::Z, 60);

  std::cout << img2dz << "\n";

  imgvol::Img2D img2dy = imgvol::Cut(img, imgvol::ImgVol::Axis::Y, 40);

  std::cout << img2dy << "\n";

  imgvol::Img2D img2dx = imgvol::Cut(img, imgvol::ImgVol::Axis::X, 40);

  std::cout << img2dx << "\n";

  imgvol::ImgVet imggray(img2dz.Data(), img2dz.SizeX(), img2dz.SizeY());
  imggray.WriteImg("test");
}
