#pragma once

#include <string>
#include <iostream>

extern "C" {
#include <image.h>
}

class ImgVol {
 public:
  enum class Axis {X, Y, Z};

  ImgVol(size_t xsize, size_t ysize, size_t zsize);

  ImgVol(std::string file_name);

  ImgVol(const ImgVol&) = delete;

  ImgVol(ImgVol&&) = delete;

  ImgVol& operator=(const ImgVol&) = delete;

  ImgVol& operator=(ImgVol&&) = delete;

  ~ImgVol();

  Image* Img();

  bool ValidVoxel(Voxel v);

  void WriteImg(std::string file_name);

  friend std::ostream& operator<<(std::ostream& stream,
                                  ImgVol& img);

 private:
  Image *img_;
};
