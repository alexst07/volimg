#pragma once

#include <string>
#include <iostream>

extern "C" {
#include <mc920.h>
}

namespace imgvol {

class ImgGray {
 public:
  ImgGray(size_t xsize, size_t ysize);

  ImgGray(const int* data, size_t xsize, size_t ysize);

  ImgGray(const ImgGray&);

  ImgGray(ImgGray&&);

  ImgGray& operator=(const ImgGray&);

  ImgGray& operator=(ImgGray&&);

  ~ImgGray();

  int operator()(size_t x, size_t y) const;

  void operator()(int v, size_t x, size_t y);

  size_t SizeX() const noexcept;

  size_t SizeY() const noexcept;

  void WriteImg(const std::string& file_name);

 private:
  void Copy(const ImgGray&);
  void Move(ImgGray&&);
  GrayImage *img_;
};

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

  MedicalImage* Img();

  int operator()(size_t x, size_t y, size_t z) const;

  int VoxelIntensity(size_t x, size_t y, size_t z) const;

  size_t SizeX() const noexcept;

  size_t SizeY() const noexcept;

  size_t SizeZ() const noexcept;

  void WriteImg(std::string file_name);

  friend std::ostream& operator<<(std::ostream& stream,
                                  ImgVol& img);

 private:
  MedicalImage *img_;
};

}
