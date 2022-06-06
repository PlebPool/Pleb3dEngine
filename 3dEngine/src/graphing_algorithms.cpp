//
// Created by matti on 2022-06-06.
//

#include "../headers/graphing_algorithms.h"

void graphing_algorithms::paintBorder(COLORREF* buffer, COLORREF color, int height, int width)
{
    for (int i = 0; i < width; i++)
    {
        buffer[(width-1)*height+i] = color;
        buffer[i] = color;
    }

    for (int i = 0; i < height; i++)
    {
        buffer[i*width] = color;
        buffer[i*width-1] = color;
    }
}

/**
 * The Bresenham line algorithm is a line drawing algorithm that determines the points of an n-dimensional raster that
 * should be selected in order to form a close approximation to a straight line between two points
 *
 * @param p1 The starting point of the line
 * @param p2 The end point of the line
 * @param buf The buffer to draw to.
 * @param height The height of the buffer
 * @param width width of the buffer
 * @param color The color of the line.
 *
 * @return A void function.
 */
void graphing_algorithms::bresenhamLine(
        graphing_structs::Vec2d &p1, graphing_structs::Vec2d &p2, COLORREF* buf, int height, int width, COLORREF &color)
{
    if (p1.x > (float)width || p1.x < 0 || p2.x > (float)width || p2.x < 0 || p1.y > (float)height || p1.y < 0
            || p2.y > (float)height || p2.y < 0)
    {
        return;
    }
    int x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;
    dx=(int)p2.x-(int)p1.x;dy=(int)p2.y-(int)p1.y;
    dx1=abs(dx);dy1=abs(dy);
    px=2*dy1-dx1;py=2*dx1-dy1;
    if(dy1<=dx1)
    {
        if(dx>=0){x=(int)p1.x;y=(int)p1.y;xe=(int)p2.x;}
        else{x=(int)p2.x;y=(int)p2.y;xe=(int)p1.x;}
        buf[y*height+x]=color;
        for(i=0;x<xe;i++)
        {
            color++;
            x=x+1;
            if(px<0){px=px+2*dy1;}
            else
            {
                if((dx<0&&dy<0)||(dx>0&&dy>0)){y=y+1;}
                else{y=y-1;}
                px=px+2*(dy1-dx1);
            }
            buf[y*height+x]=color;
        }
    }
    else
    {
        if(dy>=0){x=(int)p1.x;y=(int)p1.y;ye=(int)p2.y;}
        else{x=(int)p2.x;y=(int)p2.y;ye=(int)p1.y;}
        buf[y*height+x]=color;
        for(i=0;y<ye;i++)
        {
            color++;
            y=y+1;
            if(py<=0){py=py+2*dx1;}
            else
            {
                if((dx<0&&dy<0)||(dx>0&&dy>0)){x=x+1;}
                else{x=x-1;}
                py=py+2*(dx1-dy1);
            }
            buf[y*height+x]=color;
        }
    }
}