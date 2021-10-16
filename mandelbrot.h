#ifndef MANDELBROT_H_
#define MANDELBROT_H_

namespace bitmap_img
{
class mandelbrot
{
public:
    static const int MAX_ITERATIONS = 1000;   
public:
    mandelbrot();
    ~mandelbrot();
    static int getIterations(double x , double y);
};

} // namespace bitmap_img

#endif