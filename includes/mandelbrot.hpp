#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

#include <cstdint>
#include <string>

#include "color.hpp"
#include "complex.hpp"
#include "uselibpng.h"

// TODO: Fill in the remaining constructors, functions, and private member
// variables in this class. Render and ColorPixel are provided to you.

class Mandelbrot {
public:
  pixel_t ColorPixel(unsigned int iteration, Color color) const;
  Image Render(Color color) const;

private:
};

#endif