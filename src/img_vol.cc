#include "img_vol.h"

ImgGray::ImgGray(size_t xsize, size_t ysize) {
  img_ = CreateGrayImage(xsize, ysize);
}

ImgGray::ImgGray(int* data, size_t xsize, size_t ysize) {
  img_ = CreateGrayImage(xsize, ysize);

  for (int i = 0; i < xsize; i++) {
    for (int j = 0; j < ysize; i++) {
      img_->val[i][j] = data[i*xsize + ysize];
    }
  }
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

  memcpy(img_->val, img.img_->val, img_->nx);

  for (int i = 0; i < img_->nx; i++) {
    memcpy(img_->val[i], img.img_->val[i], img_->ny);
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
