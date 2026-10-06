typedef struct {
  double re, im;
} complex;

complex complex_new(double, double);
complex complex_sum(complex, complex);
complex complex_product(complex, complex);
double  complex_modulus(complex);

