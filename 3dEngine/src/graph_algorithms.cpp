//
// Created by mattias.wegblad on 2022-06-05.
//

#include "../headers/graph_algorithms.h"

void graph_algorithms::bresenhamLine(POINT &p1, POINT &p2, COLORREF buf[512][512], COLORREF &color)
{
    int x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;
    dx=p2.x-p1.x;dy=p2.y-p1.y;
    dx1=abs(dx);dy1=abs(dy);
    px=2*dy1-dx1;py=2*dx1-dy1;
    if(dy1<=dx1)
    {
        if(dx>=0){x=p1.x;y=p1.y;xe=p2.x;}
        else{x=p2.x;y=p2.y;xe=p1.x;}
        buf[y][x]=color;
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
            buf[y][x]=color;
        }
    }
    else
    {
        if(dy>=0){x=p1.x;y=p1.y;ye=p2.y;}
        else{x=p2.x;y=p2.y;ye=p1.y;}
        buf[y][x]=color;
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
            buf[y][x]=color;
        }
    }
}