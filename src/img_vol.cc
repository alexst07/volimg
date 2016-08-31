#include "img_vol.h"

ImgVol::ImgVol(size_t xsize, size_t ysize, size_t zsize) {
  img_ = CreateMedicalImage(xsize, ysize, zsize);
}

ImgVol::ImgVol(std::string file_name) {
  img_ = ReadMedicalImage(const_cast<char*>(file_name.c_str()));
}

ImgVol::~ImgVol() {
  DestroyMedicalImage(&img_);
}

MedicalImage* ImgVol::Img() {
  return img_;
}

void ImgVol::WriteImg(std::string file_name) {
  WriteMedicalImage(img_, const_cast<char*>(file_name.c_str()));
}

int ImgVol::VoxelIntensity(size_t x, size_t y, size_t z) const {
  return img_->val[x][y][z];
}

int ImgVol::operator()(size_t x, size_t y, size_t z) const{
  return VoxelIntensity(x, y, z);
}

size_t ImgVol::SizeX() const noexcept {
  return img_->nx;
}

size_t ImgVol::SizeY() const noexcept {
  return img_->ny;
}

size_t ImgVol::SizeZ() const noexcept {
  return img_->nz;
}

std::ostream& operator<<(std::ostream& stream,
                         ImgVol& img) {
  stream << "Img sizes[X: "<< img.Img()->nx << ", Y: " << img.Img()->ny
  << ", Z: " << img.Img()->nz << "]";
  return stream;
}
