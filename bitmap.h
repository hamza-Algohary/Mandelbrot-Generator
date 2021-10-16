#ifndef BITMAP_H_
#define BITMAP_H_

#include <string>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <memory>

using namespace std;

namespace bitmap_img
{
class bmpImg
{
private:
    int m_width{0};
    int m_height{0};
    unique_ptr<uint8_t[]> m_pixels {nullptr};
public:
    bmpImg(int width, int height);
    ~bmpImg();

    bool write(string file);
    void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
    void debug(){
        for(auto ptr = m_pixels.get();ptr < (m_pixels.get()+(m_width*m_height)) ; ptr++){
            cout << *ptr;
        }
    }
};

} // namespace bitmap_img
#endif