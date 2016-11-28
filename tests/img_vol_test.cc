#include <iostream>
#include "img_vol.h"
#include "operations.h"
#include "img2d.h"

int main(int argc, char **argv) {
  imgvol::ImgVol img("/home/alex/Downloads/libmc920/data/brain.scn");
//   imgvol::ImgVol img_label("/home/alex/Downloads/libmc920/data/brain_label.scn");
  std::cout << img << "\n";
  std::array<float,3> p1 = {50,50,0};
  std::array<float,3> pn = {50,50,100};

  imgvol::ImgGray img_gray = imgvol::MaxIntensionProjection(img, M_PI/180*30, M_PI/180*30, std::array<float, 3>{0,0,1});
  img_gray.WriteImg("mip");

//   imgvol::ImgVol img_vol = imgvol::ReformataImg(img, 100, p1, pn);
//   img_vol.WriteImg("reformat");

//   for (size_t i = 0; i < 20; i++) {
// //     imgvol::Img2D img2dz = imgvol::Cut(img_vol, imgvol::ImgVol::Axis::aZ, i);
//     std::string stri = std::to_string(i);
//     std::string name = "corte_";
//     imgvol::ImgGray planar =  imgvol::CortePlanar(img, std::array<float, 3>{30, 127, i*5},
//                                                   std::array<float, 3>{2, 3, 2});
//     planar.WriteImg(name+stri);
//   }

//   for (size_t i = 0; i < 5; i++) {
//     imgvol::Img2D img2dz = imgvol::Cut(img_vol, imgvol::ImgVol::Axis::aZ, i);
//     std::string stri = std::to_string(i);
//     std::string name = "corte_";
//     imgvol::ImgVet imggray(img2dz.Data(), img2dz.SizeX(), img2dz.SizeY());
//     imggray.WriteImg(name+stri);
//   }

//   imgvol::ImgVol imgout = Interp(img, 2, 2, 2);
//   imgvol::Img2D img2dz = imgvol::Cut(imgout, imgvol::ImgVol::Axis::aZ, 50);
//   imgvol::ImgVet imggray(img2dz.Data(), img2dz.SizeX(), img2dz.SizeY());
//   imggray.WriteImg("test");
//   imgvol::ImgGray planar =  imgvol::CortePlanar(img, std::array<float, 3>{78, 127, 127}, std::array<float, 3>{0, 0, 1});
//   planar.WriteImg("planar");

//   std::cout << img(57, 9, 35) << "\n";
//
//   imgvol::Img2D img2dz = imgvol::Cut(img, imgvol::ImgVol::Axis::Z, 100);
//   imgvol::Img2D img2dz_label = imgvol::Cut(img_label, imgvol::ImgVol::Axis::Z, 100);
//
//   std::cout << img2dz << "\n";
//
//   imgvol::Img2D img2dy = imgvol::Cut(img, imgvol::ImgVol::Axis::Y, 40);
//
//   std::cout << img2dy << "\n";
//
//   imgvol::Img2D img2dx = imgvol::Cut(img, imgvol::ImgVol::Axis::X, 40);
//
//   std::cout << img2dx << "\n";
//
//   imgvol::ImgVet imggray(img2dz.Data(), img2dz.SizeX(), img2dz.SizeY());
//   imggray.WriteImg("test");
//
//   BrightinessContrast(img2dz, 12, 60, 60);
// //   Normalize(img2dz, 12);
//   //   Negative(img2dz);
//
//   imgvol::ImgColor img_color = imgvol::ColorLabels(img2dz, img2dz_label, 16);
//   img_color.WriteImg("color_test");
//   imgvol::ImgVet imggray2(img2dz.Data(), img2dz.SizeX(), img2dz.SizeY());
//   imggray2.WriteImg("bri_contrast");
//
//   imgvol::ImgVet imggray_label(img2dz_label.Data(), img2dz_label.SizeX(), img2dz_label.SizeY());
//   imggray_label.WriteImg("mask");

//   imgvol::ImgGray cube = imgvol::DrawWireframe(img, std::array<float, 3> {M_PI/180*0, M_PI/180*45, 0});
//   imgvol::ImgGray cube = imgvol::DrawWireframe(img, std::array<float, 3> {0, 0, 0});
//   cube.WriteImg("cube");
}
