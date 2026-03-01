#include "mandelbrot.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <stdexcept>

// TODO: Define the remaining Mandelbrot member functions in this file.

// Provided to you.
// Colors each pixel. Pixels inside the Mandelbrot set
// are colored black, while a pixels outside the set
// are colored based on their escape iteration.
pixel_t Mandelbrot::ColorPixel(unsigned int iteration, Color color) const {
  pixel_t pixel{};
  pixel.a = 255;
  if (iteration >= max_iterations_) {
    pixel.r = 0;
    pixel.g = 0;
    pixel.b = 0;
    return pixel;
  }

  double intensity = std::cbrt(static_cast<double>(iteration) /
                               static_cast<double>(max_iterations_));

  Color intense_color = {int(color.Red() * intensity),
                         int(color.Green() * intensity),
                         int(color.Blue() * intensity)};

  pixel.r = intense_color.Red();
  pixel.g = intense_color.Green();
  pixel.b = intense_color.Blue();
  return pixel;
}

// Provided to you. Renders a PNG from
// your Mandelbrot implementation.
Image Mandelbrot::Render(Color color) const {
  Image img(width_, height_);
  for (unsigned int y = 0; y < height_; ++y) {
    for (unsigned int x = 0; x < width_; ++x) {
      Complex complex = PixelToComplex(x, y);
      unsigned int iteration = EscapeIterations(complex);
      img[y][x] = ColorPixel(iteration, color);
    }
  }
  return img;
}