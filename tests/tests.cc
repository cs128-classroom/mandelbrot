#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <stdexcept>

#include "catch.hpp"
#include "color.hpp"
#include "complex.hpp"
#include "grader_support.hpp"
#include "mandelbrot.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Color RGB default to 0", "[Color1]") {
  Color c;
  REQUIRE(c.*sol::stowed<sol::color_red_tag>::value == 0);
  REQUIRE(c.*sol::stowed<sol::color_green_tag>::value == 0);
  REQUIRE(c.*sol::stowed<sol::color_blue_tag>::value == 0);
}
TEST_CASE("Color constructor assigns valid values correctly", "[Color2]") {
  Color c(21, 19, 3);
  REQUIRE(c.*sol::stowed<sol::color_red_tag>::value == 21);
  REQUIRE(c.*sol::stowed<sol::color_green_tag>::value == 19);
  REQUIRE(c.*sol::stowed<sol::color_blue_tag>::value == 3);
}
TEST_CASE("Color constructor clamps values correctly", "[Color3]") {
  Color c(-1, -1, -1);
  REQUIRE(c.*sol::stowed<sol::color_red_tag>::value == 0);
  REQUIRE(c.*sol::stowed<sol::color_green_tag>::value == 0);
  REQUIRE(c.*sol::stowed<sol::color_blue_tag>::value == 0);
  Color c2(256, 256, 256);
  REQUIRE(c2.*sol::stowed<sol::color_red_tag>::value == 255);
  REQUIRE(c2.*sol::stowed<sol::color_green_tag>::value == 255);
  REQUIRE(c2.*sol::stowed<sol::color_blue_tag>::value == 255);
}
TEST_CASE("Color getters obtain correct result", "[Color4]") {
  Color c;
  auto& red = c.*sol::stowed<sol::color_red_tag>::value;
  auto& green = c.*sol::stowed<sol::color_green_tag>::value;
  auto& blue = c.*sol::stowed<sol::color_blue_tag>::value;
  red = 2;
  green = 1;
  blue = 3;
  REQUIRE(c.Red() == 2);
  REQUIRE(c.Green() == 1);
  REQUIRE(c.Blue() == 3);
}

TEST_CASE("Complex defaults to (0,0)", "[Complex1]") {
  Complex c;
  auto& real = c.*sol::stowed<sol::complex_real_tag>::value;
  auto& imag = c.*sol::stowed<sol::complex_imaginary_tag>::value;
  REQUIRE(real == 0.0);
  REQUIRE(imag == 0.0);
}

TEST_CASE("Complex paramaterized constructor obtains correct result",
          "[Complex2]") {
  Complex c(-1.5, 8.8);
  auto& real = c.*sol::stowed<sol::complex_real_tag>::value;
  auto& imag = c.*sol::stowed<sol::complex_imaginary_tag>::value;
  REQUIRE(real == -1.5);
  REQUIRE(imag == 8.8);
}

TEST_CASE("Complex Real/Imaginary obtain correct result", "[Complex3]") {
  Complex c;
  auto& real = c.*sol::stowed<sol::complex_real_tag>::value;
  auto& imag = c.*sol::stowed<sol::complex_imaginary_tag>::value;
  real = 2.22;
  imag = -5.55;
  REQUIRE(c.Real() == 2.22);
  REQUIRE(c.Imaginary() == -5.55);
}

TEST_CASE("Complex SetReal/Imaginary obtain correct result", "[Complex4]") {
  Complex c;
  auto& real = c.*sol::stowed<sol::complex_real_tag>::value;
  auto& imag = c.*sol::stowed<sol::complex_imaginary_tag>::value;
  c.SetReal(3.14);
  c.SetImaginary(-0.001);
  REQUIRE(real == 3.14);
  REQUIRE(imag == -0.001);
}
TEST_CASE("Complex MagnitudeSquared obtains correct result", "[Complex5]") {
  // return real_ * real_ + imaginary_ * imaginary_;
  Complex c;
  auto& real = c.*sol::stowed<sol::complex_real_tag>::value;
  auto& imag = c.*sol::stowed<sol::complex_imaginary_tag>::value;
  real = -1.5;
  imag = 8.2;
  double expected = std::sqrt(-1.5 * -1.5 + 8.2 * 8.2);
  REQUIRE(c.Magnitude() == expected);
}
TEST_CASE("Complex Add obtains correct result", "[Complex6]") {
  Complex c;
  auto& real = c.*sol::stowed<sol::complex_real_tag>::value;
  auto& imag = c.*sol::stowed<sol::complex_imaginary_tag>::value;
  real = 1.0;
  imag = -4.5;
  Complex c2;
  auto& real2 = c2.*sol::stowed<sol::complex_real_tag>::value;
  auto& imag2 = c2.*sol::stowed<sol::complex_imaginary_tag>::value;
  real2 = -6.0;
  imag2 = 2.5;
  Complex c3 = c.Add(c2);
  REQUIRE(c3.*sol::stowed<sol::complex_real_tag>::value == -5.0);
  REQUIRE(c3.*sol::stowed<sol::complex_imaginary_tag>::value == -2.0);
}
TEST_CASE("Complex Multiply obtains correct result", "[Complex7]") {
  Complex c;
  auto& real = c.*sol::stowed<sol::complex_real_tag>::value;
  auto& imag = c.*sol::stowed<sol::complex_imaginary_tag>::value;
  real = 1.0;
  imag = -4.5;
  Complex c2;
  auto& real2 = c2.*sol::stowed<sol::complex_real_tag>::value;
  auto& imag2 = c2.*sol::stowed<sol::complex_imaginary_tag>::value;
  real2 = -6.0;
  imag2 = 2.5;
  Complex c3 = c.Multiply(c2);
  REQUIRE(c3.*sol::stowed<sol::complex_real_tag>::value == 5.25);
  REQUIRE(c3.*sol::stowed<sol::complex_imaginary_tag>::value == 29.5);
}

TEST_CASE("Mandelbrot constructor sets height and width", "[Mandelbrot1]") {
  Mandelbrot m(900, 700);
  auto& h = m.*sol::stowed<sol::mandelbrot_height_tag>::value;
  auto& w = m.*sol::stowed<sol::mandelbrot_width_tag>::value;
  REQUIRE(h == 700);
  REQUIRE(w == 900);
}
TEST_CASE("Mandelbrot constructor throws invalid", "[Mandelbrot2]") {
  REQUIRE_THROWS(Mandelbrot(1, 0));
  REQUIRE_THROWS(Mandelbrot(0, 1));
}

TEST_CASE("Mandelbrot PixelToComplex accounts for scale", "[Mandelbrot4]") {
  Mandelbrot m(101, 37);
  Complex comp_center;
  auto& real_center = comp_center.*sol::stowed<sol::complex_real_tag>::value;
  auto& imag_center =
      comp_center.*sol::stowed<sol::complex_imaginary_tag>::value;
  real_center = 12.5;
  imag_center = -9.0;
  m.*sol::stowed<sol::mandelbrot_center_tag>::value = comp_center;

  // measure the span across the image at one scale
  m.*sol::stowed<sol::mandelbrot_scale_tag>::value = 1.0;
  Complex left1 = m.PixelToComplex(0, 12);
  Complex right1 = m.PixelToComplex(100, 12);
  double span1 = right1.*sol::stowed<sol::complex_real_tag>::value -
                 left1.*sol::stowed<sol::complex_real_tag>::value;

  // measure the span again at a factor of the scale
  auto scale = m.*sol::stowed<sol::mandelbrot_scale_tag>::value = 3.0;
  Complex left2 = m.PixelToComplex(0, 12);
  Complex right2 = m.PixelToComplex(100, 12);
  double span2 = right2.*sol::stowed<sol::complex_real_tag>::value -
                 left2.*sol::stowed<sol::complex_real_tag>::value;

  // if scale is set correctly, span should shrink inversely
  REQUIRE(span2 == Approx(span1 / scale));
}
TEST_CASE("Mandelbrot PixelToComplex maintains aspect ratio", "[Mandelbrot5]") {
  // ratio of the imaginary span to the real span should equal height/width.
  Mandelbrot m(200, 50);

  Complex center;
  center.*sol::stowed<sol::complex_real_tag>::value = -13.0;
  center.*sol::stowed<sol::complex_imaginary_tag>::value = 7.0;
  m.*sol::stowed<sol::mandelbrot_center_tag>::value = center;
  m.*sol::stowed<sol::mandelbrot_scale_tag>::value = 1.7;

  unsigned int mid_x = 100;
  unsigned int mid_y = 25;

  double real_left =
      m.PixelToComplex(0, mid_y).*sol::stowed<sol::complex_real_tag>::value;
  double real_right =
      m.PixelToComplex(199, mid_y).*sol::stowed<sol::complex_real_tag>::value;
  const double real_span = real_right - real_left;

  double imag_top = m.PixelToComplex(mid_x, 0).*
                    sol::stowed<sol::complex_imaginary_tag>::value;
  double imag_bottom = m.PixelToComplex(mid_x, 49).*
                       sol::stowed<sol::complex_imaginary_tag>::value;
  double imag_span = imag_top - imag_bottom;

  REQUIRE((imag_span / real_span) == Approx(50.0 / 200.0));
}

TEST_CASE("Mandelbrot PixelToComplex accounts for center", "[Mandelbrot6]") {
  Mandelbrot m(101, 51);
  m.*sol::stowed<sol::mandelbrot_scale_tag>::value = 2.25;

  Complex desired_center;
  desired_center.*sol::stowed<sol::complex_real_tag>::value = 1.234;
  desired_center.*sol::stowed<sol::complex_imaginary_tag>::value = -0.987;
  m.*sol::stowed<sol::mandelbrot_center_tag>::value = desired_center;

  // center pixel should map to center
  Complex got_center = m.PixelToComplex(50, 25);
  REQUIRE(got_center.*sol::stowed<sol::complex_real_tag>::value ==
          Approx(desired_center.*sol::stowed<sol::complex_real_tag>::value));
  REQUIRE(
      got_center.*sol::stowed<sol::complex_imaginary_tag>::value ==
      Approx(desired_center.*sol::stowed<sol::complex_imaginary_tag>::value));

  // shifting the center should shift every pixel by the same delta
  Complex before = m.PixelToComplex(17, 3);

  Complex shifted_center;
  shifted_center.*sol::stowed<sol::complex_real_tag>::value =
      desired_center.*sol::stowed<sol::complex_real_tag>::value + 0.5;
  shifted_center.*sol::stowed<sol::complex_imaginary_tag>::value =
      desired_center.*sol::stowed<sol::complex_imaginary_tag>::value - 2.0;

  m.*sol::stowed<sol::mandelbrot_center_tag>::value = shifted_center;

  Complex after = m.PixelToComplex(17, 3);

  REQUIRE(after.*sol::stowed<sol::complex_real_tag>::value -
              before.*sol::stowed<sol::complex_real_tag>::value ==
          Approx(0.5));
  REQUIRE(after.*sol::stowed<sol::complex_imaginary_tag>::value -
              before.*sol::stowed<sol::complex_imaginary_tag>::value ==
          Approx(-2.0));
}

TEST_CASE("Mandelbrot PixelToComplex obtains correct result", "[Mandelbrot7]") {
  Mandelbrot m(5, 3);
  Complex center;
  center.*sol::stowed<sol::complex_real_tag>::value = 1.0;
  center.*sol::stowed<sol::complex_imaginary_tag>::value = -2.0;
  m.*sol::stowed<sol::mandelbrot_center_tag>::value = center;
  m.*sol::stowed<sol::mandelbrot_scale_tag>::value = 4.0;

  const double expected_left = 0.875;
  const double expected_top = -1.925;

  // (0,0) should map to (left, top)
  Complex z1 = m.PixelToComplex(0, 0);
  REQUIRE(z1.*sol::stowed<sol::complex_real_tag>::value ==
          Approx(expected_left));
  REQUIRE(z1.*sol::stowed<sol::complex_imaginary_tag>::value ==
          Approx(expected_top));

  // (2,1) should map to center
  Complex z2 = m.PixelToComplex(2, 1);
  REQUIRE(z2.*sol::stowed<sol::complex_real_tag>::value ==
          Approx(center.*sol::stowed<sol::complex_real_tag>::value));
  REQUIRE(z2.*sol::stowed<sol::complex_imaginary_tag>::value ==
          Approx(center.*sol::stowed<sol::complex_imaginary_tag>::value));

  // (4, 2) should map to bottom right corner
  Complex z3 = m.PixelToComplex(4, 2);
  REQUIRE(z3.*sol::stowed<sol::complex_real_tag>::value == Approx(1.125));
  REQUIRE(z3.*sol::stowed<sol::complex_imaginary_tag>::value == Approx(-2.075));
}
TEST_CASE("Mandelbrot EscapeIterations uses Mandelbrot set formula",
          "[Mandelbrot8]") {
  Mandelbrot m(10, 10);
  m.*sol::stowed<sol::mandelbrot_max_iterations_tag>::value = 20;

  Complex c1;
  c1.*sol::stowed<sol::complex_real_tag>::value = 2.0;
  c1.*sol::stowed<sol::complex_imaginary_tag>::value = 0.0;
  REQUIRE(m.EscapeIterations(c1) == 1);

  // catches using >= 2, wrong update order, or wrong recurrence
  Complex c2;
  c2.*sol::stowed<sol::complex_real_tag>::value = 1.0;
  c2.*sol::stowed<sol::complex_imaginary_tag>::value = 0.0;
  REQUIRE(m.EscapeIterations(c2) == 2);

  // if the implementation uses the wrong sign (e.g. z^2 - c), this will fail
  Complex c3;
  c3.*sol::stowed<sol::complex_real_tag>::value = -1.0;
  c3.*sol::stowed<sol::complex_imaginary_tag>::value = 0.0;
  REQUIRE(m.EscapeIterations(c3) == 20);

  // catches incorrect complex multiply / magnitude logic
  Complex c4;
  c4.*sol::stowed<sol::complex_real_tag>::value = 0.0;
  c4.*sol::stowed<sol::complex_imaginary_tag>::value = 2.0;
  REQUIRE(m.EscapeIterations(c4) == 1);
}

TEST_CASE("Mandelbrot EscapeIterations obtains correct result",
          "[Mandelbrot9]") {
  Mandelbrot m(10, 10);

  // returns max iterations when necessary
  m.*sol::stowed<sol::mandelbrot_max_iterations_tag>::value = 7;

  Complex c0;
  c0.*sol::stowed<sol::complex_real_tag>::value = 0.0;
  c0.*sol::stowed<sol::complex_imaginary_tag>::value = 0.0;
  REQUIRE(m.EscapeIterations(c0) == 7);

  // returns smaller-than-max iteration when necessary
  Complex c2;
  c2.*sol::stowed<sol::complex_real_tag>::value = 2.0;
  c2.*sol::stowed<sol::complex_imaginary_tag>::value = 0.0;
  REQUIRE(m.EscapeIterations(c2) == 1);
}
