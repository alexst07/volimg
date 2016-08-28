#include "img_vol.h"

ImgVol::ImgVol(size_t xsize, size_t ysize, size_t zsize) {
  img_ = CreateImage(xsize, ysize, zsize);
}

ImgVol::ImgVol(std::string file_name) {
  img_ = ReadImage(const_cast<char*>(file_name.c_str()));
}

ImgVol::~ImgVol() {
  DestroyImage(img_);
}

Image* ImgVol::Img() {
  return img_;
}

bool ImgVol::ValidVoxel(Voxel v) {
  return ::ValidVoxel(img_, v);
}

void ImgVol::WriteImg(std::string file_name) {
  WriteImage(img_, const_cast<char*>(file_name.c_str()));
}

std::ostream& operator<<(std::ostream& stream,
                         ImgVol& img) {
  stream << "Img sizes[X: "<< img.Img()->xsize << ", Y: " << img.Img()->ysize
  << ", Z: " << img.Img()->zsize << "]";
  return stream;
                         }
