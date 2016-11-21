#pragma once

#include "img_vol.h"
#include "img2d.h"

namespace imgvol {

Img2D Cut(const ImgVol& img_vol, ImgVol::Axis axis, size_t pos);

void BrightinessContrast(Img2D& img, size_t num_bits, float b, float c);

void Normalize(Img2D& img, size_t num_bits);

void Negative(Img2D& img);

ImgColor ColorLabels(const Img2D& img_cut, const Img2D& img_lb, size_t nbits);

ImgGray DrawWireframe(const ImgVol& img_vol, std::array<float, 3> rad);

ImgVol Interp(ImgVol& img_vol, float sx, float sy, float sz);

float Sign(float v);

ImgVol Refactor(const ImgVol& img_vol, float dx2, float dy2, float dz2);

float Diagonal(std::array<float, 3> size);

ImgGray CortePlanar(ImgVol& img, std::array<float, 3> p1, std::array<float, 3> vec);

ImgVol ReformataImg(ImgVol& img, size_t n, std::array<float,3> p1, std::array<float,3> pn);
}
