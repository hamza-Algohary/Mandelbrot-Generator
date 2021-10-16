#include <fstream>
#include "bmp_headers.h"
#include "bitmap.h"

using namespace bitmap_img;
using namespace std;

bmpImg::bmpImg(int width , int height): m_width(width) , m_height(height) , m_pixels(new uint8_t[width*height*3]{}){

}
bmpImg::~bmpImg(){

}

/*void bmpImg::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue){
    uint8_t *pixel = m_pixels.get();
    pixel += (y*3*m_width) + (x*3);

    pixel[0] = blue;
    pixel[1] = green;
    pixel[2] = red;
}*/


void bmpImg::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
	uint8_t *pPixel = m_pixels.get();

	pPixel += (y * 3) * m_width + (x * 3);

	pPixel[0] = blue;
	pPixel[1] = green;
	pPixel[2] = red;
}


bool bmpImg::write(string file_name){
    bmpFileHeader fHeader;
    bmpInfoHeader iHeader;

    fHeader.fileSize = sizeof(bmpInfoHeader) + sizeof(bmpFileHeader) + (m_width*m_height*3);
    fHeader.dataOffSet = sizeof(bmpInfoHeader) + sizeof(bmpFileHeader);

    iHeader.width = m_width;
    iHeader.height = m_height;

    fstream file(file_name , ios::out|ios::binary);

    if(!file){
        return false;
    }

    file.write((char *)&fHeader , sizeof(fHeader));
    file.write((char *)&iHeader , sizeof(iHeader));
	file.write((char *) m_pixels.get(), m_width * m_height * 3);                                                                //unique_ptr<>.get() //What does get() method does is that it returns a raw pointer to the actual bytes pointed by the smartpointer
                                                                //,We need this here because we cannot cast a unique_ptr<> to (char *) directly

    return true;
}