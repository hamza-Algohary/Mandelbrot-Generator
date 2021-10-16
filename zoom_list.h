#ifndef ZOOMLIST_H_
#define ZOOMLIST_H_
#include "zoom.h"
#include <vector>
#include <utility>

using namespace std;

namespace bitmap_img
{
class zoom_list
{
private:
    double m_xCenter{0};
    double m_yCenter{0};
    double m_scale{1.0};

    int m_width;
    int m_height;
    vector<zoom> zooms;
public:
    zoom_list(int width , int height);
    void add(const zoom& zm);
    pair<double , double> doZoom(int x,int y);
};

} // namespace bitmap_img

#endif