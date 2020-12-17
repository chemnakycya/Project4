#ifndef TRIGPOLY_H
#define TRIGPOLY_H

typedef double Dtype;

class TrigPoly {
public:
    size_t n;      //size of polynomial
    double alpha;  // starting real number a0
    double *a;     //coefficients of sin
    double *b;     // coefficients of cos

    TrigPoly(size_t x, double angle);
    TrigPoly();
    ~TrigPoly();
};
//// Generating a random trigonometric polynomial of the n degree
extern TrigPoly generate_TrigPoly(int n);
//
//// Trigonometric polynomial input/output
extern int input_TrigPoly(TrigPoly* x);
extern void output_TrigPoly(TrigPoly x, int type, int width, int precision);
//
//// Basic math functions for TrigPoly
extern double value_x(TrigPoly p, Dtype x);
extern TrigPoly add_TrigPoly(TrigPoly x, TrigPoly y);
extern TrigPoly sub_TrigPoly(TrigPoly x, TrigPoly y);
extern TrigPoly mul_TrigPoly(TrigPoly x, TrigPoly y);
//
//// Derivative, undefined integral and defined integral functions
extern TrigPoly derivative(TrigPoly p);
extern TrigPoly integral (TrigPoly p, Dtype C);
extern Dtype integrate(TrigPoly p, Dtype a, Dtype b);
//

#endif //TRIGPOLY_H
