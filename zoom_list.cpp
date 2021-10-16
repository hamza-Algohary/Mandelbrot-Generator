/*#include "zoom_list.h"
#include <iostream>

using namespace bitmap_img;

zoom_list::zoom_list(int width,int height):m_width(width) , m_height(height){
}

void zoom_list::add(const zoom& zm){
    zooms.push_back(zm); 

    //m_xCenter +=  zm.x -(m_width/2) * m_scale;
    //m_yCenter +=  zm.y -(m_height/2)* m_scale;   
    //Another implementaion (in the two next lines)

    m_xCenter += zm.x - (m_width/2);
    m_yCenter += zm.y - (m_height/2);

    m_scale *= zm.scale;

    std::cout << m_xCenter << " " << m_yCenter << " " << m_scale << std::endl;
}

pair<double , double>zoom_list::doZoom(int x,int y){
    double virtualX = (x - m_width/2  + m_xCenter) * m_scale;
    double virtualY = (y - m_height/2 + m_yCenter) * m_scale;

    cout << x << " " << y << " " << virtualX << " " << virtualY << endl;
    //double virtualX = (x - m_width / 2) * m_scale + m_xCenter;
	//double virtualY = (y - m_height / 2) * m_scale + m_yCenter;
    
    return make_pair(virtualX , virtualY);
}*/


/*
 * ZoomList.cpp
 *
 *  Created on: Sep 20, 2015
 *      Author: johnpurcell
 
*/
#include "zoom_list.h"
#include <iostream>

using namespace std;

namespace bitmap_img
{

zoom_list::zoom_list(int width, int height) : m_width(width), m_height(height)
{
    // TODO Auto-generated constructor stub
}

void zoom_list::add(const zoom &zm)
{
    zooms.push_back(zm);

    m_xCenter += (zm.x - m_width / 2) * m_scale;
    m_yCenter += (zm.y - m_height / 2) * m_scale;

    m_scale *= zm.scale;

    cout << m_xCenter << ", " << m_yCenter << ", " << m_scale << endl;
}

pair<double, double> zoom_list::doZoom(int x, int y)
{
    double xFractal = (x - m_width / 2) * m_scale + m_xCenter;
    double yFractal = (y - m_height / 2) * m_scale + m_yCenter;

    return pair<double, double>(xFractal, yFractal);
}

}  // namespace caveofprogramming