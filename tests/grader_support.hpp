#ifndef MYCLASS_GRADER_SUPPORT_H
#define MYCLASS_GRADER_SUPPORT_H

#include <string>
#include <vector>

#include "color.hpp"
#include "complex.hpp"
#include "mandelbrot.hpp"

namespace sol {
  // The chunk below should not need to change
  // -----start---------
  template <class Tag>
  struct stowed {
    static typename Tag::type value;
  };

  template <class Tag>
  typename Tag::type stowed<Tag>::value;

  template <class Tag, typename Tag::type x>
  class stow_private {
    stow_private() { stowed<Tag>::value = x; }
    static stow_private instance;
  };

  template <class Tag, typename Tag::type x>
  stow_private<Tag, x> stow_private<Tag, x>::instance;
  //---------------end---------------------

  // Make a tag for each of your variables:

  // COLOR
  // red_ green_ blue_ kColorValueMin kColorValueMax
  struct color_red_tag {
    typedef int(Color::*type);
  };

  struct color_green_tag {
    typedef int(Color::*type);
  };

  struct color_blue_tag {
    typedef int(Color::*type);
  };

  struct color_kColorValueMin_tag {
    typedef const int(Color::*type);
  };

  struct color_kColorValueMax_tag {
    typedef const int(Color::*type);
  };

  // MANDELBROT
  // kWidth kHeight center_ scale_
  // max_iterations_
  struct mandelbrot_width_tag {
    typedef unsigned int(Mandelbrot::*type);
  };

  struct mandelbrot_height_tag {
    typedef unsigned int(Mandelbrot::*type);
  };

  struct mandelbrot_center_tag {
    typedef Complex(Mandelbrot::*type);
  };

  struct mandelbrot_scale_tag {
    typedef double(Mandelbrot::*type);
  };

  struct mandelbrot_max_iterations_tag {
    typedef unsigned int(Mandelbrot::*type);
  };

  // COMPLEX
  // real_ imaginary_
  struct complex_real_tag {
    typedef double(Complex::*type);
  };

  struct complex_imaginary_tag {
    typedef double(Complex::*type);
  };

  // Explicit instantiations to stow private member pointers, one needed for
  // each variable:

  // COLOR
  template class stow_private<color_red_tag, &Color::red_>;
  template class stow_private<color_green_tag, &Color::green_>;
  template class stow_private<color_blue_tag, &Color::blue_>;
  template class stow_private<color_kColorValueMin_tag, &Color::kColorValueMin>;
  template class stow_private<color_kColorValueMax_tag, &Color::kColorValueMax>;

  // MANDELBROT
  template class stow_private<mandelbrot_width_tag, &Mandelbrot::width_>;
  template class stow_private<mandelbrot_height_tag, &Mandelbrot::height_>;
  template class stow_private<mandelbrot_center_tag, &Mandelbrot::center_>;
  template class stow_private<mandelbrot_scale_tag, &Mandelbrot::scale_>;
  template class stow_private<mandelbrot_max_iterations_tag,
                              &Mandelbrot::max_iterations_>;

  // COMPLEX
  template class stow_private<complex_real_tag, &Complex::real_>;
  template class stow_private<complex_imaginary_tag, &Complex::imaginary_>;

}  // namespace sol

#endif  // MYCLASS_GRADER_SUPPORT_H