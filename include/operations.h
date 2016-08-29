#pragma once

#include "img_vol.h"
#include "img2d.h"

Img2D Cut(const ImgVol& img_vol, ImgVol::Axis axis, size_t pos, int graus);
