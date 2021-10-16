#ifndef BMP_HEADERS_H_
#define BMP_HEADERS_H_
#include <cstdint>

using namespace std;

#pragma pack(2)

namespace bitmap_img{

struct bmpFileHeader
{
public:
    char header[2] = {'B' , 'M'};
    int32_t fileSize;
    int32_t reserved{0};
    int32_t dataOffSet;
};

struct bmpInfoHeader
{
    int32_t headerSize{40};
    int32_t width;
    int32_t height;
    int16_t planes{1};
    int16_t bitsPerPixel{24};
    int32_t compression{0};
    int32_t dataSize;
    int32_t horizontalResolution;
    int32_t verticalResoultion;
    int32_t colors{0};
    int32_t importantColors{0};
};


}
#endif