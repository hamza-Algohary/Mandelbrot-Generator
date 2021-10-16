#ifndef RGB_H_
#define RGB_H_

struct RGB
{   int red;
    int green;
    int blue;

    RGB(int red, int green, int blue) : red(red), green(green), blue(blue)
    {
    }

    void setColor(int red, int green, int blue)
    {
        this->red = red;
        this->green = green;
        this->blue = blue;
    }

    RGB operator-(const RGB &rgb)
    {
        return RGB(red - rgb.red, green - rgb.green, blue - rgb.blue);
    }
};

#endif