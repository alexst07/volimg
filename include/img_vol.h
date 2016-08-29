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

  int operator()(size_t x, size_t y, size_t z) const;

  int VoxelIntensity(size_t x, size_t y, size_t z) const;

  bool ValidVoxel(Voxel v) const noexcept;

  size_t SizeX() const noexcept;

  size_t SizeY() const noexcept;

  size_t SizeZ() const noexcept;

  void WriteImg(std::string file_name);

  friend std::ostream& operator<<(std::ostream& stream,
                                  ImgVol& img);

 private:
  Image *img_;
};
