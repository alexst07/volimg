#pragma once

#include <string>
#include <array>
#include <iostream>

extern "C" {
#include <mc920.h>
}

namespace imgvol {

class ImgColor {
 public:
  ImgColor() = delete;

  ImgColor(size_t xsize, size_t ysize);

  ImgColor(const ImgColor&);

  ImgColor(ImgColor&&);

  ImgColor& operator=(const ImgColor&);

  ImgColor& operator=(ImgColor&&);

  ~ImgColor();

  std::array<int, 3> operator()(size_t x, size_t y) const;

  void operator()(std::array<int, 3> v, size_t x, size_t y);

  void operator()(std::array<int, 3> v, size_t i);

  size_t SizeX() const noexcept;

  size_t SizeY() const noexcept;

  void WriteImg(const std::string& file_name);

 private:
  void Copy(const ImgColor&);
  void Move(ImgColor&&);
  ColorImage *img_;
};

class ImgVet {
 public:
  ImgVet(size_t xsize, size_t ysize);

  ImgVet(const int* data, size_t xsize, size_t ysize);

  ImgVet(const ImgVet&);

  ImgVet(ImgVet&&);

  ImgVet& operator=(const ImgVet&);

  ImgVet& operator=(ImgVet&&);

  ~ImgVet();

  int operator()(size_t x, size_t y) const;

  void operator()(int v, size_t x, size_t y);

  size_t SizeX() const noexcept;

  size_t SizeY() const noexcept;

  void WriteImg(const std::string& file_name);

 private:
  void Copy(const ImgVet&);
  void Move(ImgVet&&);
  Image *img_;
};

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

  ImgVol(ImgVol&& img) {
    img_ = img.img_;
    img.img_ = nullptr;
  }

  ImgVol& operator=(const ImgVol&) = delete;

  ImgVol& operator=(ImgVol&& img) {
    img_ = img.img_;
    img.img_ = nullptr;
  }

  ~ImgVol();

  MedicalImage* Img();

  int operator()(size_t x, size_t y, size_t z) const;

  int VoxelIntensity(size_t x, size_t y, size_t z) const;

  void SetVoxelIntensity(float b, size_t x, size_t y, size_t z);

  size_t SizeX() const noexcept;

  size_t SizeY() const noexcept;

  size_t SizeZ() const noexcept;

  float DimX() const noexcept;

  float DimY() const noexcept;

  float DimZ() const noexcept;

  void WriteImg(std::string file_name);

  friend std::ostream& operator<<(std::ostream& stream,
                                  ImgVol& img);

 private:
  MedicalImage *img_;
};

}
