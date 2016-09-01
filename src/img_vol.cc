#include "img_vol.h"

namespace imgvol {

ImgGray::ImgGray(size_t xsize, size_t ysize) {
  img_ = CreateGrayImage(xsize, ysize);
}

ImgGray::ImgGray(const int* data, size_t xsize, size_t ysize) {
  img_ = CreateGrayImage(xsize, ysize);

  for (int i = 0; i < ysize; i++) {
    for (int j = 0; j < xsize; j++) {
      img_->val[i][j] = data[i*xsize + j];
    }
  }
}

ImgGray::~ImgGray() {
  DestroyGrayImage(&img_);
}

ImgGray::ImgGray(ImgGray&& img) {
  Move(std::move(img));
}

ImgGray::ImgGray(const ImgGray& img) {
  Copy(img);
}

ImgGray& ImgGray::operator=(ImgGray&& img) {
  Move(std::move(img));
  return *this;
}

ImgGray& ImgGray::operator=(const ImgGray& img) {
  Copy(img);
  return *this;
}

void ImgGray::Copy(const ImgGray& img) {
  img_->dx = img.img_->dx;
  img_->dy = img.img_->dy;
  img_->nx = img.img_->nx;
  img_->ny = img.img_->ny;
  memcpy(img_->unid, img.img_->unid, 10);

  memcpy(img_->val, img.img_->val, img_->ny);

  for (int i = 0; i < img_->ny; i++) {
    memcpy(img_->val[i], img.img_->val[i], img_->nx);
  }
}

void ImgGray::Move(ImgGray&& img) {
  img_->dx = img.img_->dx;
  img_->dy = img.img_->dy;
  img_->nx = img.img_->nx;
  img_->ny = img.img_->ny;
  memcpy(img_->unid, img.img_->unid, 10);
  img_->val = img.img_->val;

  img.img_->dx = 0;
  img.img_->dy = 0;
  img.img_->nx = 0;
  img.img_->ny = 0;
  img.img_->val = nullptr;
}


void ImgGray::operator()(int v, size_t x, size_t y) {
  img_->val[y][x] = v;
}

int ImgGray::operator()(size_t x, size_t y) const {
  return img_->val[y][x];
}

void ImgGray::WriteImg(const std::string& file_name) {
  WriteGrayImage(img_, const_cast<char*>(file_name.c_str()));
}

size_t ImgGray::SizeX() const noexcept {
  return img_->nx;
}

size_t ImgGray::SizeY() const noexcept {
  return img_->ny;
}

/////////////////////////////////////////////////////////////////////////

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
  return img_->val[z][y][x];
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

}
