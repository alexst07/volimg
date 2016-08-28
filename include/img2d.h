#pragma once

#include <vector>
#include <memory>

class Img2D {
  Img2D(int *data, size_t xsize, size_t ysize)
  : xsize_(xsize), ysize_(ysize), pixels_(data, xsize*ysize) {}

  Img2D(const Img2D& img)
  : xsize_(img.xsize_), ysize_(img.ysize_), pixels_(img.pixels_) {}

  Img2D4(Img2D&& img)
  : xsize_(img.xsize_), ysize_(img.ysize_), pixels_(std::move(img.pixels_)) {
    img.xsize_ = 0;
    img.ysize_ = 0;
  }

  Img2D& operator=(const Img2D& img) {
    xsize_ = img.xsize_;
    ysize_ = img.ysize_;
    pixels_ = img.pixels_;

    return *this;
  }

  Img2D& operator=(Img2D&& img) {
    xsize_ = img.xsize_;
    ysize_ = img.ysize_;
    pixels_ = std::move(img.pixels_);

    img.xsize_ = 0;
    img.ysize_ = 0;

    return *this;
  }

 private:
  std::vector<int> pixels_;
  size_t xsize_;
  size_t ysize_;
};
