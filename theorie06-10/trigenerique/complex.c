#include <math.h>
#include "complex.h"

complex complex_new(double re, double im) {
  complex c;
  c.re = re;
  c.im = im;
  return c;
}

complex complex_sum(complex a, complex b) {
  complex c;
  c.re = a.re + b.re;
  c.im = a.im + b.im;
  return c;
}

complex complex_product(complex a, complex b) {
  complex c;
  c.re = a.re * b.re - a.im * b.im;
  c.im = a.re * b.im + a.im * b.re;
  return c;
}

double complex_modulus(complex c) {
  return sqrt(c.re*c.re + c.im*c.im);
}

