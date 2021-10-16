#include <iostream>
#include <memory>
#include <cmath>
#include <vector>
#include "fractal.h"
#include "rgb.h"

using namespace std;
using namespace bitmap_img;

const int WIDTH = 800;
const int HEIGHT = 600;

bmpImg image(WIDTH, HEIGHT);

double originalScale = HEIGHT / 2;
double scale = originalScale;

//pair<int, int> positionToZoom = make_pair(368, 30); //A beautiful image
pair<int, int> positionToZoom = make_pair(WIDTH/2, HEIGHT/2); // Original position of the image
//pair<int, int> positionToZoom = make_pair(300, 220); // Original position of the image

int main()
{
    cout << "Processing image >_\n";

    FractalCreator fractalCreator(WIDTH, HEIGHT, originalScale, scale, positionToZoom);
    fractalCreator.addColorRange(0  , RGB(0, 0, 0));
    fractalCreator.addColorRange(0.3, RGB(255, 0, 0));
    fractalCreator.addColorRange(0.5, RGB(255 , 255, 0));
    fractalCreator.addColorRange(1.0, RGB(255, 255, 255));

    cout << fractalCreator.getRange(999) << endl;
    fractalCreator.createFractal();

    cout << "Finished!\n";
}