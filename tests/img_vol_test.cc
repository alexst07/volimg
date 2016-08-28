#include <iostream>
#include "img_vol.h"

int main(int argc, char **argv) {
  ImgVol img("/home/alex/Downloads/libmo815-3dvis/data/brain.scn");
  std::cout << img;
}
