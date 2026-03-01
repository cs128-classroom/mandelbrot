#include <cstdint>
#include <iostream>
#include <string>

#include "mandelbrot.hpp"

int main() {
  // Once you complete the Color, Complex, and Mandelbrot classes, uncomment the
  // code below to generate a Mandelbrot set image! Have fun experimenting with
  // different parameters and colors!

  /*
  Play around with the height, width, and maximum
  iterations! But, be mindful that the image may
  take a while to generate if you use large numbers.

  std::string out = "mandelbrot.png";
  unsigned int width = 1000;
  unsigned int height = 800;
  int max_iters = 200;

  Mandelbrot m(width, height);
  m.SetMaxIterations(max_iters);

  Try changing these for zoom explorations:

  m.SetCenter(Complex(-0.5, 0.0));
  m.SetScale(1.0 / 3.0);

  Try passing different RGB color values into the Render function!

  Color color = {10, 128, 60};
  Image img = m.Render(color);
  img.save(out.c_str());
  */

  return 0;
}