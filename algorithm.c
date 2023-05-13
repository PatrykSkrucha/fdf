#include "include/fdf.h"

void BresenhamLine(const int x1, const int y1, const int x2, const int y2, mlx_image_t* img)
 {
     // zmienne pomocnicze
     int d, dx, dy, ai, bi, xi, yi;
     int x = x1, y = y1;
     // ustalenie kierunku rysowania
     if (x1 < x2)
     {
         xi = 1;
         dx = x2 - x1;
     }
     else
     {
         xi = -1;
         dx = x1 - x2;
     }
     // ustalenie kierunku rysowania
     if (y1 < y2)
     {
         yi = 1;
         dy = y2 - y1;
     }
     else
     {
         yi = -1;
         dy = y1 - y2;
     }
     // pierwszy piksel
     mlx_put_pixel(img, x, y, 0xff0000d9);
     // oś wiodąca OX
     if (dx > dy)
     {
         ai = (dy - dx) * 2;
         bi = dy * 2;
         d = bi - dx;
         // pętla po kolejnych x
         while (x != x2)
         {
             // test współczynnika
             if (d >= 0)
             {
                 x += xi;
                 y += yi;
                 d += ai;
             }
             else
             {
                 d += bi;
                 x += xi;
             }
			 mlx_put_pixel(img, x, y, 0xff0000d9);
         }
     }
     // oś wiodąca OY
     else
     {
         ai = ( dx - dy ) * 2;
         bi = dx * 2;
         d = bi - dy;
         // pętla po kolejnych y
         while (y != y2)
         {
             // test współczynnika
             if (d >= 0)
             {
                 x += xi;
                 y += yi;
                 d += ai;
             }
             else
             {
                 d += bi;
                 y += yi;
             }
             mlx_put_pixel(img, x, y, 0xff0000d9);
         }
     }
 }