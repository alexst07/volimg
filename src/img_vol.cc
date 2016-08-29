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

bool ImgVol::ValidVoxel(Voxel v) const noexcept {
  return ::ValidVoxel(img_, v);
}

void ImgVol::WriteImg(std::string file_name) {
  WriteImage(img_, const_cast<char*>(file_name.c_str()));
}

int ImgVol::VoxelIntensity(size_t x, size_t y, size_t z) const {
  size_t pos = x + y*img_->xsize + z*img_->xsize*img_->ysize;
  return img_->val[pos];
}

int ImgVol::operator()(size_t x, size_t y, size_t z) const{
  return VoxelIntensity(x, y, z);
}

size_t ImgVol::SizeX() const noexcept {
  return img_->xsize;
}

size_t ImgVol::SizeY() const noexcept {
  return img_->ysize;
}

size_t ImgVol::SizeZ() const noexcept {
  return img_->zsize;
}

std::ostream& operator<<(std::ostream& stream,
                         ImgVol& img) {
  stream << "Img sizes[X: "<< img.Img()->xsize << ", Y: " << img.Img()->ysize
  << ", Z: " << img.Img()->zsize << "]";
  return stream;
}
