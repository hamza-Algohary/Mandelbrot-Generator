#ifndef ZOOM_H_
#define ZOOM_H_

namespace bitmap_img
{
struct zoom
{
    int x{0} , y{0};
    double scale{0.0};

    zoom(int x ,int y ,double scale): x(x) , y(y) , scale(scale){
        
    }
};
} // namespace bitmap_img

#endif