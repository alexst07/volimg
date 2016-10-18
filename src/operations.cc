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

  if (axis == ImgVol::Axis::aZ) {
    s1 = img_vol.SizeX();
    s2 = img_vol.SizeY();
  } else if (axis == ImgVol::Axis::aX) {
    s1 = img_vol.SizeZ();
    s2 = img_vol.SizeY();
  } else {
    s1 = img_vol.SizeZ();
    s2 = img_vol.SizeX();
  }

  Img2D img2d(s1, s2);

  for (int i = 0; i < s1; i++) {
    for (int j = 0; j < s2; j++) {
      if (axis == ImgVol::Axis::aZ) {
        img2d(img_vol(i, j, pos), i, j);
      } else if (axis == ImgVol::Axis::aX) {
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

  b = 100 -b;
  c = 100 -c;

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
      cor[0] = h*std::max(float(0), (3- abs(v-4) - abs(v - 5))/2);
      cor[1] = h*std::max(float(0), (4- abs(v-2) - abs(v - 4))/2);
      cor[2] = h*std::max(float(0), (3- abs(v-1) - abs(v - 2))/2);
      img_color(cor, i);
    } else {
      cor[0] = cor[1] = cor[2] = img_cut[i];
      img_color(cor, i);
    }
  }

  return img_color;
}

ImgVol CortePlanar(ImgVol& img, std::array<float, 3> p1, std::array<float, 3> vec) {
  // Handle vec[2] = 0
  float alpha_x = atan(vec[1]/ vec[2]);

  if (vec[2] < 0) {
    alpha_x += M_PI;
  }

  float vzl = vec[2]/cos(alpha_x);
  std::array<float, 3> qc = {img.SizeX()/2, img.SizeY()/2, img.SizeZ()/2};

  float alpha_y = atan(vec[0]/ vzl);
  Matrix *t_mqc = CreateMatrix(4, 4);
  t_mqc->val[0] = 1;
  t_mqc->val[1] = 0;
  t_mqc->val[2] = 0;
  t_mqc->val[3] = -qc[0];
  t_mqc->val[4] = 0;
  t_mqc->val[5] = 1;
  t_mqc->val[6] = 0;
  t_mqc->val[7] = -qc[1];
  t_mqc->val[8] = 0;
  t_mqc->val[9] = 0;
  t_mqc->val[10] = 1;
  t_mqc->val[11] = -qc[2];
  t_mqc->val[12] = 0;
  t_mqc->val[13] = 0;
  t_mqc->val[14] = 0;
  t_mqc->val[15] = 1;

  Matrix *rotx = CreateMatrix(4, 4);
  rotx->val[0] = 1;
  rotx->val[1] = 0;
  rotx->val[2] = 0;
  rotx->val[3] = 0;
  rotx->val[4] = 0;
  rotx->val[5] = cos(-alpha_x);
  rotx->val[6] = -sin(-alpha_x);
  rotx->val[7] = 0;
  rotx->val[8] = 0;
  rotx->val[9] = sin(-alpha_x);
  rotx->val[10] = cos(-alpha_x);
  rotx->val[11] = 0;
  rotx->val[12] = 0;
  rotx->val[13] = 0;
  rotx->val[14] = 0;
  rotx->val[15] = 1;

  Matrix *roty = CreateMatrix(4, 4);
  roty->val[0] = cos(alpha_y);
  roty->val[1] = 0;
  roty->val[2] = sin(alpha_y);
  roty->val[3] = 0;
  roty->val[4] = 0;
  roty->val[5] = 1;
  roty->val[6] = 0;
  roty->val[7] = 0;
  roty->val[8] = -sin(alpha_y);
  roty->val[9] = 0;
  roty->val[10] = cos(alpha_y);
  roty->val[11] = 0;
  roty->val[12] = 0;
  roty->val[13] = 0;
  roty->val[14] = 0;
  roty->val[15] = 1;

  Matrix *t_p1 = CreateMatrix(4, 4);
  t_p1->val[0] = 1;
  t_p1->val[1] = 0;
  t_p1->val[2] = 0;
  t_p1->val[3] = p1[0];
  t_p1->val[4] = 0;
  t_p1->val[5] = 1;
  t_p1->val[6] = 0;
  t_p1->val[7] = p1[1];
  t_p1->val[8] = 0;
  t_p1->val[9] = 0;
  t_p1->val[10] = 1;
  t_p1->val[11] = p1[2];
  t_p1->val[12] = 0;
  t_p1->val[13] = 0;
  t_p1->val[14] = 0;
  t_p1->val[15] = 1;

  Matrix *tmp_rx_tqc = MultMatrices(rotx, t_mqc);
  Matrix* tmp_ry_rx_tqc = MultMatrices(roty, tmp_rx_tqc);
  Matrix *phi_inv = MultMatrices(t_p1, tmp_ry_rx_tqc);

  float diagonal = Diagonal(std::array<float, 3>{img.SizeX(), img.SizeY(), img.SizeZ()});

  ImgGray img_out(diagonal, diagonal);
  Matrix *q = CreateMatrix(4, 1);

  for (int u = 0; u < (int) diagonal; u++) {
    for (int v = 0; v < (int) diagonal; v++) {
      q->val[0] = u;
      q->val[1] = v;
      q->val[2] = -diagonal/2;
      q->val[3] = 1;

      Matrix *p = MultMatrices(phi_inv, q);
      int intensity;

      if (p->val[0] < 0 || p->val[1] < 0 || p->val[2] < 0)
        intensity = 0;
      else  if (p->val[0] > img.SizeX() || p->val[1] < img.SizeY() || p->val[2] > img.SizeZ())
        intensity = 0;
      else {
        Point point{p->val[0], p->val[1], p->val[2]};
        intensity = ImageValueAtPoint(img.Img(), point);
      }
    }
  }

}

std::array<float, 3> Translate(std::array<float, 3> point, std::array<float, 3> dist) {
  std::array<float, 3> p;
  p[0] = point[0] + dist[0];
  p[1] = point[1] + dist[1];
  p[2] = point[2] + dist[2];

  return p;
}

std::array<float, 3> RotateZ(std::array<float, 3> point, float rad) {
  std::array<float, 3> p;
  p[0] = cos(rad)*point[0] - sin(rad)*point[1];
  p[1] = sin(rad)*point[0] + cos(rad)*point[1];
  p[2] = point[2];

  return p;
}

std::array<float, 3> RotateX(std::array<float, 3> point, float rad) {
  std::array<float, 3> p;
  p[0] = point[0];
  p[1] = cos(rad)*point[1] - sin(rad)*point[2];
  p[2] = sin(rad)*point[1] + cos(rad)*point[2];

  return p;
}

std::array<float, 3> RotateY(std::array<float, 3> point, float rad) {
  std::array<float, 3> p;
  p[0] = cos(rad)*point[0] + sin(rad)*point[2];
  p[1] = point[1];
  p[2] = -sin(rad)*point[0] + cos(rad)*point[2];

  return p;
}

float DotProduct(std::array<float, 3> vec) {
  std::array<float, 3> ref = {0, 0, -1};

  float res = ref[0]*vec[0];
  res += ref[1]*vec[1];
  res += ref[2]*vec[2];

  return res;
}

float Diagonal(std::array<float, 3> size) {
  float res = size[0]*size[0] + size[1]*size[1] + size[2]*size[2];
  res = sqrt(res);
}

bool TestVisibleFace(std::array<float, 3> face, std::array<float, 3> rad) {
  std::array<float, 3> fp = RotateX(face, rad[0]);
  fp = RotateY(fp, rad[1]);
  fp = RotateZ(fp, rad[2]);

  float dot_prod = DotProduct(fp);

  if (dot_prod > 0)
    return true;

  return false;
}

std::array<bool, 6> VisibleFaces(std::array<float, 3> rad) {
  std::vector<std::array<float, 3>> faces = {{1, 0, 0}, {-1, 0, 0},
                                             {0, 1, 0}, {0, -1, 0},
                                             {0, 0, 1}, {0, 0, -1}};

  std::array<bool, 6> res;
  int i = 0;
  for (const auto& f: faces) {
    res[i] = TestVisibleFace(f, rad);
    i++;
  }

  return res;
}

std::vector<std::array<float, 3>> VertexWireframe(const ImgVol& img_vol, std::array<float, 3> rad) {
  std::array<float, 3> size;
  size[0] = img_vol.SizeX();
  size[1] = img_vol.SizeY();
  size[2] = img_vol.SizeZ();
  std::array<float, 3> dist_center = {-size[0]/2, -size[1]/2, -size[2]/2};

  float diagonal = Diagonal(size);

  // Conferir o -diagonal/2
  std::array<float, 3> dist_diagonal = {diagonal/2, diagonal/2, -diagonal/2};

  std::vector<std::array<size_t, 3>> in_vec = {{0, 0, 0}, {img_vol.SizeX(), 0, 0},
                                              {0, img_vol.SizeY(), 0}, {img_vol.SizeX(), img_vol.SizeY(), 0},
                                              {0, 0, img_vol.SizeZ()}, {img_vol.SizeX(), 0, img_vol.SizeZ()},
                                              {0, img_vol.SizeY(), img_vol.SizeZ()},
                                              {img_vol.SizeX(), img_vol.SizeY(), img_vol.SizeZ()}};

  std::vector<std::array<float, 3>> out_vec;

  for (const auto& e: in_vec) {
    std::array<float, 3> point = {e[0], e[1], e[2]};
    std::array<float, 3> fp = Translate(point, dist_center);
    fp = RotateX(fp, rad[0]);
    fp = RotateY(fp, rad[1]);
    fp = RotateZ(fp, rad[2]);
    fp = Translate(fp, dist_diagonal);
    out_vec.push_back(fp);
  }

  return out_vec;
}

float Sign(float v) {
  if (v < 0)
    return -1;
  else if (v == 0)
    return 0;
  else
    return 1;
}

void DrawLine(std::array<float, 3> p1, std::array<float, 3> p2, ImgGray& img) {
  int n;
  float Du, Dv;
  float du, dv;

  if (p1 == p2)
    n = 1;
  else {
    Du = p2[0] - p1[0];
    Dv = p2[1] - p1[1];

    if (abs(Du) >= abs(Dv)) {
      n = abs(Du) + 1;
      du = Sign(Du);
      dv = du * Dv/Du;
    } else {
      n = abs(Dv) + 1;
      dv = Sign(Dv);
      du = dv * Du/Dv;
    }
  }

  std::array<float, 3> p = p1;
  for (int k = 0; k < n; k++) {
    img(255, p[0], p[1]);
    p[0] += du;
    p[1] += dv;
  }
}

ImgGray DrawWireframe(const ImgVol& img_vol, std::array<float, 3> rad) {
  std::array<float, 3> size;
  size[0] = img_vol.SizeX();
  size[1] = img_vol.SizeY();
  size[2] = img_vol.SizeZ();

  std::array<float, 3> dist_center = {-size[0]/2, -size[1]/2, -size[2]/2};

  float diagonal = Diagonal(size);

  // Conferir o -diagonal/2
  std::array<float, 3> dist_diagonal = {diagonal/2, diagonal/2, -diagonal/2};

  ImgGray res_img(diagonal, diagonal);

  std::vector<std::array<float, 3>> vertex = VertexWireframe(img_vol, rad);

  std::array<bool, 6> faces = VisibleFaces(rad);

  for (auto f: faces) {
    std::cout << "faces: " << f << "\n";
  }

  if (faces[5]) {
    DrawLine(vertex[0], vertex[1], res_img);
    DrawLine(vertex[0], vertex[2], res_img);
    DrawLine(vertex[1], vertex[3], res_img);
    DrawLine(vertex[2], vertex[3], res_img);
  }

  if (faces[3]) {
    DrawLine(vertex[0], vertex[1], res_img);
    DrawLine(vertex[0], vertex[4], res_img);
    DrawLine(vertex[1], vertex[5], res_img);
    DrawLine(vertex[4], vertex[5], res_img);
  }

  if (faces[0]) {
    DrawLine(vertex[1], vertex[5], res_img);
    DrawLine(vertex[1], vertex[3], res_img);
    DrawLine(vertex[3], vertex[7], res_img);
    DrawLine(vertex[5], vertex[7], res_img);
  }

  if (faces[1]) {
    DrawLine(vertex[0], vertex[4], res_img);
    DrawLine(vertex[0], vertex[2], res_img);
    DrawLine(vertex[4], vertex[6], res_img);
    DrawLine(vertex[2], vertex[6], res_img);
  }

  if (faces[4]) {
    DrawLine(vertex[4], vertex[5], res_img);
    DrawLine(vertex[4], vertex[6], res_img);
    DrawLine(vertex[5], vertex[7], res_img);
    DrawLine(vertex[6], vertex[7], res_img);
  }

  if (faces[2]) {
    DrawLine(vertex[2], vertex[3], res_img);
    DrawLine(vertex[2], vertex[6], res_img);
    DrawLine(vertex[6], vertex[7], res_img);
    DrawLine(vertex[3], vertex[7], res_img);
  }

  return res_img;
}

ImgVol Interp(ImgVol& img_vol, float sx, float sy, float sz) {
  MedicalImage* img = Interp(img_vol.Img(), sx, sy, sz);
  ImgVol img_out(img);

  return img_out;
}

}
