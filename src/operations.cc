#include <limits>
#include <array>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <random>
#include <map>
#include "operations.h"

namespace imgvol {

Img2D Cut(const ImgVol& img_vol, ImgVol::Axis axis, size_t pos) {
  size_t s1, s2;

  if (axis == ImgVol::Axis::Z) {
    s1 = img_vol.SizeX();
    s2 = img_vol.SizeY();
  } else if (axis == ImgVol::Axis::X) {
    s1 = img_vol.SizeZ();
    s2 = img_vol.SizeY();
  } else {
    s1 = img_vol.SizeZ();
    s2 = img_vol.SizeX();
  }

  Img2D img2d(s1, s2);

  for (int i = 0; i < s1; i++) {
    for (int j = 0; j < s2; j++) {
      if (axis == ImgVol::Axis::Z) {
        img2d(img_vol(i, j, pos), i, j);
      } else if (axis == ImgVol::Axis::X) {
        img2d(img_vol(pos, j, i), i, j);
      } else {
        img2d(img_vol(j, pos, i), i, j);
      }
    }
  }

  return img2d;
}

std::array<size_t, 2> MinMax(const Img2D& img) {
  size_t min = std::numeric_limits<size_t>::max();
  size_t max = std::numeric_limits<size_t>::min();

  auto data = img.Data();

  for (int i = 0; i < img.NumPixels(); i++) {
    if (data[i] < min)
      min = data[i];

    if (data[i] > max)
      max = data[i];
  }

  std::array<size_t, 2> arr = {min, max};
  return arr;
}

void Normalize(Img2D& img, size_t num_bits) {
  int h = pow(2, num_bits) - 1;
  float k1 = 0, k2 = h;
  float i1 = MinMax(img)[0];

  float i2 = MinMax(img)[1];

  for (size_t i = 0; i < img.NumPixels(); i++) {
    if (img[i] < i1)
      img[i] = k1;

    if (img[i] >= i1 && img[i] < i2)
      img[i] = int(((k2 - k1)/(i2-i1))*(img[i] - i1) + k1);

    if (img[i] >= i2)
      img[i] = k2;
  }

}

void Negative(Img2D& img) {
  float k1 = MinMax(img)[1], k2 = MinMax(img)[0];
  float i1 = MinMax(img)[0];

  float i2 = MinMax(img)[1];

  for (size_t i = 0; i < img.NumPixels(); i++) {
    if (img[i] < i1)
      img[i] = k1;

    if (img[i] >= i1 && img[i] < i2)
      img[i] = int(((k2 - k1)/(i2-i1))*(img[i] - i1) + k1);

    if (img[i] >= i2)
      img[i] = k2;
  }
}

void BrightinessContrast(Img2D& img, size_t num_bits, float b, float c) {
//   size_t h = pow(2, num_bits) - 1;
  float h = MinMax(img)[1];

  float k1 = 0;
  float k2 = h;

  float b_real = (b/100)*h;
  float c_real = (c/100)*h;

  float i1 = (2*b_real - c_real)/2;
  float i2 = (c_real + 2*b_real)/2;
//   float i2 = i1;

  std::cout << "i1: " << i1 << " i2: " << i2 << "\n";

  for (size_t i = 0; i < img.NumPixels(); i++) {
    if (img[i] < i1)
      img[i] = k1;

    if (img[i] >= i1 && img[i] < i2)
      img[i] = int(((k2 - k1)/(i2-i1))*(img[i] - i1) + k1);

    if (img[i] >= i2)
      img[i] = k2;
  }
}

ImgColor ColorLabels(const Img2D& img_cut, const Img2D& img_lb, size_t nbits) {
  std::map<int, int> tab_color;
  std::default_random_engine generator;

  float h = pow(2, nbits) - 1;
  std::uniform_int_distribution<int> distribution(0,int(h));
  ImgColor img_color(img_cut.SizeX(), img_cut.SizeY());
  std::array<int, 3> cor;

  for (int i = 0; i < img_lb.NumPixels(); i++) {
    if (img_lb[i] == 0) {
      cor[0] = cor[1] = cor[2] = img_cut[i];
      img_color(cor, i);
      continue;
    }

    if (i%2 == 0) {
      int p = img_lb[i];

      if (tab_color.find(p) == tab_color.end())
        tab_color.insert(std::pair<int, int>(p, distribution(generator)));

      int m = tab_color[p];

      float v = m/h;
      std::cout << "v: " << v << "  ";
      v = 4*v +1;
      cor[0] = h*std::max(0, (3- abs(v-4) - abs(v - 5))/2);
      cor[1] = h*std::max(0, (4- abs(v-2) - abs(v - 4))/2);
      cor[2] = h*std::max(0, (3- abs(v-1) - abs(v - 2))/2);
      img_color(cor, i);
    } else {
      cor[0] = cor[1] = cor[2] = img_cut[i];
      img_color(cor, i);
    }
  }

  return img_color;
}

}
