#pragma once

#include "img_vol.h"
#include "img2d.h"

namespace imgvol {

Img2D Cut(const ImgVol& img_vol, ImgVol::Axis axis, size_t pos);

}
