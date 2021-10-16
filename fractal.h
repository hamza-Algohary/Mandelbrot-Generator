#include <string>
#include <iostream>
#include <utility>
#include <memory>
#include <cmath>
#include <vector>
#include <assert.h>

#include "bitmap.h"
#include "mandelbrot.h"
#include "rgb.h"

using namespace std;

namespace bitmap_img
{
class FractalCreator
{
private:
    int WIDTH;
    int HEIGHT;
    bmpImg image;

    double originalScale;
    double scale;
    pair<int, int> positionToZoom;

    vector<double> colorRanges;
    vector<RGB> colors;
    vector<int> rangeTotals;

    bool m_bGotFirstRange{false};
    //map<colorRanges>

    unique_ptr<int[]> histogram; // an array to store the number of pixels for eachnumber of iterations
                                 //(where the index = number of iterations)

    unique_ptr<int[]> fractal; //An array to store the number of iterations for each pixel(where the pixel
                               //position-represented in the formula(y*width+x)- is the index)

    pair<double, double> doZoom(int x, int y, int WIDTH, int HEIGHT, double originalScale, double scale, pair<int, int> positionToZoom)
    {
        double xCenter = (positionToZoom.first - (WIDTH / 2.0)) / originalScale;
        double yCenter = (HEIGHT - positionToZoom.second - (HEIGHT / 2.0)) / originalScale;

        if (y == 0 && x == 0)
        {
            cout << xCenter << " " << yCenter << endl;
        }
        double fractalX = (x - (WIDTH / 2.0) - WIDTH / 4) / scale + xCenter; //offset then scaling
        double fractalY = (y - (HEIGHT / 2.0)) / scale + yCenter;

        return make_pair(fractalX, fractalY);
    }

public:
    FractalCreator(int WIDTH, int HEIGHT, double originalScale, double scale, pair<int, int> positionToZoom) : histogram(new int[mandelbrot::MAX_ITERATIONS + 1]()), fractal(new int[WIDTH * HEIGHT]), WIDTH(WIDTH), HEIGHT(HEIGHT), image(WIDTH, HEIGHT), originalScale(originalScale), scale(scale), positionToZoom(positionToZoom)
    {
    }
    ~FractalCreator() {}

    void addColorRange(double range, RGB color)
    {
        colorRanges.push_back(range * mandelbrot::MAX_ITERATIONS);
        colors.push_back(color);

        if (m_bGotFirstRange)
        {
            rangeTotals.push_back(0);
        }
        m_bGotFirstRange = true;
    }

    void calculateRangeTotals()
    {
        int rangeIndex = 0;

        for (int i = 0; i < mandelbrot::MAX_ITERATIONS; i++)
        {
            int pixels = histogram[i];
            if (i >= colorRanges[rangeIndex + 1])
            {
                rangeIndex++;
            }
            rangeTotals[rangeIndex] += pixels;
        }
    }

    int getRange(int iterations) const
    {
        int range = 0;

        for (int i = 0; i < colorRanges.size(); i++)
        {
            range = i;
            if (iterations < colorRanges[i + 1])
            {
                break;
            }
        }

        assert(range > -1);
        assert(range < colorRanges.size());

        return range;
    }

    void createFractal()
    {
        calculateIterations();
        calculateRangeTotals();
        drawFractal();
        writeBitmap("image.bmp");
    }

    void calculateIterations()
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                //uint8_t color = (uint8_t)(256 * ((double)iterations / mandelbrot::MAX_ITERATIONS));

                pair<double, double> cartesian = doZoom(x, y, WIDTH, HEIGHT, originalScale, scale, positionToZoom);

                int iterations = mandelbrot::getIterations(cartesian.first, cartesian.second);

                fractal[(y * WIDTH) + x] = iterations;
                if (iterations != mandelbrot::MAX_ITERATIONS)
                {
                    histogram[iterations]++;
                }
            }
            if (y % 80 == 0)
            {
                cout << "-" << flush;
            }
        }
        cout << "\n";
    }
    void drawFractal()
    {
        int total = 0;
        for (int i = 0; i < mandelbrot::MAX_ITERATIONS; i++)
        {
            total += histogram[i];
        }

        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                int iterations = fractal[(y * WIDTH) + x];
                uint8_t red{0}, green{0}, blue{0};

                int range = getRange(iterations);
                int rangeTotal = rangeTotals[range];
                int rangeStart = colorRanges[range];

                RGB startColor = colors[range];
                RGB endColor = colors[range + 1];
                RGB colorDiff = endColor - startColor;

                if (iterations == mandelbrot::MAX_ITERATIONS) //for setting black pixels (If disabled the image body won't be black)
                {
                    red = 0;
                    green = 0;
                    blue = 0;
                }
                else //for other colors
                {
                    int totalPixels{0};
                    double hue = 0.0;
                    for (int i = 0; i <= iterations; i++)
                    {
                        totalPixels += histogram[i];
                        //hue += ((double)histogram[i]) / total;
                    }

                    red = startColor.red + colorDiff.red * (double)totalPixels/rangeTotal;
                    green = startColor.green + colorDiff.green * (double)totalPixels/rangeTotal;
                    blue = startColor.blue + colorDiff.blue * (double)totalPixels/rangeTotal;
                }

                image.setPixel(x, y, red, green, blue);
            }
        }
    }

    void writeBitmap(string filename)
    {
        image.write(filename);
    }
};
} // namespace bitmap_img