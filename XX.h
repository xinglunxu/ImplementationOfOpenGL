//
//  XX.h
//  opengl
//
//  Created by xinglunxu on 12/13/14.
//
//

#ifndef __opengl__XX__
#define __opengl__XX__

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include "MatrixStack.h"
const int dimx = 800;
const int dimy = 800;
struct vertice
{
    double x, y ,z, w;
    vertice(double x_, double y_, double z_, double w_):x(x_),y(y_),z(z_),w(w_){}
    vertice():x(0),y(0),z(0),w(0){}
};

class XX{
private:
    bool buffer[dimy][dimx];
    float z_buffer[dimy][dimx];
    MatrixStack* ms;
    vertice quad_vertices[4];
    vertice tri_vertices[3];
    int VerticesRequired;
    int VerticeNumber;
    void drawLine(vertice point0, vertice point1);
    float FindZ(vertice p0, vertice p1, float x, float y);
    float analyticalEquation(vertice p0, vertice p1, vertice p);
    void drawPoint(float x, float y, float z);
    void CoverPoint(float x, float y, float z);
    void BufferTri(vertice p0, vertice p1, vertice p2);
    void DrawQuad(void);
    void DrawTri(void);
public:
    XX(MatrixStack*);
    void XXBegin(int);
    void XXEnd();
    void XXVertex3f(float,float,float);
    bool getBuffer(int,int);
    void ClearBuffer(void);
};



#endif /* defined(__opengl__XX__) */
