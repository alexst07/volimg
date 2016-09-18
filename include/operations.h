#pragma once

#include "img_vol.h"
#include "img2d.h"

namespace imgvol {

Img2D Cut(const ImgVol& img_vol, ImgVol::Axis axis, size_t pos);

void BrightinessContrast(Img2D& img, size_t num_bits, float b, float c);

void Normalize(Img2D& img, size_t num_bits);

void Negative(Img2D& img);

ImgColor ColorLabels(const Img2D& img_cut, const Img2D& img_lb, size_t nbits);

}
