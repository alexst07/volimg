#pragma once

#include <vector>
#include <memory>

namespace imgvol {

class Img2D {
 public:
  Img2D(int *data, size_t xsize, size_t ysize)
  : xsize_(xsize), ysize_(ysize), pixels_(xsize*ysize, *data) {}

  Img2D(size_t xsize, size_t ysize)
  : xsize_(xsize), ysize_(ysize), pixels_(xsize*ysize) {}

  Img2D(const Img2D& img)
  : xsize_(img.xsize_), ysize_(img.ysize_), pixels_(img.pixels_) {}

  Img2D(Img2D&& img)
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

  void operator()(int v, size_t xsize, size_t ysize) {
    pixels_[ysize*xsize_ + xsize] = v;
  }

  int operator()(size_t xsize, size_t ysize) {
    return pixels_[ysize*xsize_ + xsize];
  }

  size_t SizeX() const noexcept {
    return xsize_;
  }

  size_t SizeY() const noexcept {
    return ysize_;
  }

  size_t NumPixels() const noexcept {
    return pixels_.size();
  }

  const int* Data() const noexcept {
    return pixels_.data();
  }

  int& operator[](size_t i) {
    return pixels_[i];
  }

  const int& operator[](size_t i) const {
    return pixels_[i];
  }

 private:
  std::vector<int> pixels_;
  size_t xsize_;
  size_t ysize_;
};

}
