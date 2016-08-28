#pragma once

#include <string>
#include <image.h>

class ImgVol {
 public:
  enum class Axis {X, Y, Z};

  ImgVol(size_t xsize, size_t ysize, size_t zsize) {
    img_ = CreateImage(xsize, ysize, zsize);
  }

  ImgVol(std::string file_name) {
    img_ = ReadImage(file_name.c_str());
  }

  ImgVol(const ImgVol&) = delete;

  ImgVol(ImgVol&&) = delete;

  ImgVol& operator=(const ImgVol&) = delete;

  ImgVol& operator=(ImgVol&&) = delete;

  ~ImgVol() {
    DestroyImage(img_);
  }

  Image* Img() {
    return img_;
  }

 private:
  Image *img_;
};
