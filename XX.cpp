//
//  XX.cpp
//  opengl
//
//  Created by xinglunxu on 12/13/14.
//
//

#include "XX.h"

void XX::drawLine(vertice point0, vertice point1)
{
    float x0 = point0.x, y0 = point0.y;
    float x1 = point1.x, y1 = point1.y;
    float z;
    float m =(y1-y0)/(x1-x0);
    float drawX, drawY, d;
    if(x0 == x1)
    {
        drawX = x0;
        if(y1<y0){drawLine(point1,point0); return;}
        for(int y = y0; y<=y1; y++)
        {
            drawY = y;
            z = FindZ(point0,point1,drawX, drawY);
            drawPoint(drawX, drawY, z+0.01);
        }
        
        return;
    }
    if(m>=0 && m<=1)
    {
        if(x1<x0){drawLine(point1,point0); return;}
        drawY = y0;
        d = (y0-y1)*(x0+1)+(x1-x0)*(y0+0.5)+x0*y1-x1*y0;
        for(int x = x0; x<=x1; x++)
        {
            drawX = x;
            z = FindZ(point0,point1,drawX, drawY);
            drawPoint(drawX, drawY, z+0.01);
            if(d<0)
            {
                drawY += 1;
                d += (x1 - x0) + (y0 - y1);
            }
            else{d += (y0 - y1);}
        }
    }
    if(m>1)
    {
        if(x1<x0){drawLine(point1,point0); return;}
        drawX = x0;
        d = (x0-x1)*(y0+1)+(y1-y0)*(x0+0.5)+y0*x1-y1*x0;
        for(int y = y0; y<=y1; y++)
        {
            drawY = y;
            z = FindZ(point0,point1,drawX, drawY);
            drawPoint(drawX, drawY, z+0.01);
            if(d<0)
            {
                drawX += 1;
                d += (y1 - y0) + (x0 - x1);
            }
            else{d += (x0 - x1);}
        }
    }
    if(m<0 && m>=-1)
    {
        if(x1<x0){drawLine(point1,point0); return;}
        y1 += 2*(y0-y1);
        drawY = y0;
        d = (y0-y1)*(x0+1)+(x1-x0)*(y0+0.5)+x0*y1-x1*y0;
        for(int x = x0; x<=x1; x++)
        {
            drawX = x;
            z = FindZ(point0,point1,drawX, drawY);
            drawPoint(drawX, drawY-2*(drawY-y0), z+0.01);
            if(d<0)
            {
                drawY += 1;
                d += (x1 - x0) + (y0 - y1);
            }
            else{d += (y0 - y1);}
        }
    }
    if(m<-1)
    {
        if(x0>x1){drawLine(point1,point0); return;}
        y1 += 2*(y0-y1);
        drawX = x0;
        d = (x0-x1)*(y0+1)+(y1-y0)*(x0+0.5)+y0*x1-y1*x0;
        for(int y = y0; y<=y1; y++)
        {
            drawY = y;
            z = FindZ(point0,point1,drawX, drawY);
            drawPoint(drawX, drawY-2*(drawY-y0), z+0.01);
            if(d<0)
            {
                drawX += 1;
                d += (y1 - y0) + (x0 - x1);
            }
            else{d += (x0 - x1);}
        }
    }
    
    
}

float XX::FindZ(vertice p0, vertice p1, float x, float y)
{
    float x0 = p0.x, y0 = p0.y, z0 = p0.z;
    float _x = p1.x - x0, _y = p1.y - y0, _z = p1.z - z0;
    float t;
    if(_x != 0){t = (x-x0)/_x; return z0 + t*_z;}
    else if(_y!=0){t = (y-y0)/_y; return z0 + t*_z;}
    else {return 1001;}
}

float XX::analyticalEquation(vertice p0, vertice p1, vertice p)
{
    float x0 = p0.x, y0 = p0.y;
    float x1 = p1.x, y1 = p1.y;
    float x = p.x, y = p.y;
    return (y0-y1)*x+(x1-x0)*y+x0*y1-x1*y0;
}

void XX::drawPoint(float x, float y, float z)
{
    int drawX = x + dimx/2, drawY = -(y) + dimy/2;
    if(drawX<dimx && drawY < dimy)
    {
        if(z >= z_buffer[drawY][drawX])
        {
            z_buffer[drawY][drawX] = z;
            buffer[drawY][drawX] = 1;
        }
    }
//    else{std::cout<<"out of range";}
}

void XX::CoverPoint(float x, float y, float z)
{
    int drawX = x + dimx/2, drawY = -(y) + dimy/2;
    if(drawX<dimx && drawY < dimy)
    {
        if(z >= z_buffer[drawY][drawX])
        {
            buffer[drawY][drawX] = 0;
            z_buffer[drawY][drawX] = z;
        }
    }
//    else{std::cout<<"out of range";}
}

void XX::BufferTri(vertice p0, vertice p1, vertice p2)
{
    int minx = std::min(p0.x, (std::min(p1.x,p2.x)));
    int maxx = std::max(p0.x, (std::max(p1.x,p2.x)));
    
    int miny = std::min(p0.y, (std::min(p1.y,p2.y)));
    int maxy = std::max(p0.y, (std::max(p1.y,p2.y)));
    
    float alpha, beta, gamma;
    for(int Y = miny; Y<maxy; Y++)
    {
        for(int X = minx; X<maxx; X++)
        {
//            std::cout<<maxx<<" "<<maxy<<std::endl;
            vertice p(X, Y, 0, 1);
            alpha = analyticalEquation(p1,p2,p)/analyticalEquation(p1,p2,p0);
            beta = analyticalEquation(p2,p0,p)/analyticalEquation(p2,p0,p1);
            gamma = analyticalEquation(p0,p1,p)/analyticalEquation(p0,p1,p2);
            float Z = alpha*p0.z+beta*p1.z+gamma*p2.z;
//            std::cout<<Z<<std::endl;
            if(alpha>0 && beta>0 && gamma > 0)CoverPoint(X,Y,Z);
        }
    }
}

XX::XX(MatrixStack* ms)
{
    this->ms = ms;
    for(int j = 0; j<dimy; j++)
    {
        for(int i = 0; i<dimx; i++){buffer[j][i] = 0;}
        for(int i = 0; i<dimx; i++){z_buffer[j][i] = -1000.0;}
    }
    
}

void XX::DrawQuad(void)
{
    for(int i = 0; i<4; i++)
    {
        float vector[4][1] = {{quad_vertices[i].x},{quad_vertices[i].y},{quad_vertices[i].z},{quad_vertices[i].w}};
        ms->MultiMatrix4by1(vector);
        ms->DivideWComponent(vector);
        quad_vertices[i].x = vector[0][0];
        quad_vertices[i].y = vector[1][0];
        quad_vertices[i].z = vector[2][0];
        quad_vertices[i].w = vector[3][0];
    }
    ms->PushMatrix();
    ms->LoadIdentityMatrix();
    ms->ViewportMatrix(dimx, dimy);//
    for(int i = 0; i<4; i++)
    {
        float vector[4][1] = {{quad_vertices[i].x},{quad_vertices[i].y},{quad_vertices[i].z},{quad_vertices[i].w}};
        ms->MultiMatrix4by1(vector);
        quad_vertices[i].x = vector[0][0];
        quad_vertices[i].y = vector[1][0];
        quad_vertices[i].z = vector[2][0];
        quad_vertices[i].w = vector[3][0];
    }
    ms->PopMatrix();
    drawLine(quad_vertices[0],quad_vertices[1]);
    drawLine(quad_vertices[1],quad_vertices[2]);
    drawLine(quad_vertices[2],quad_vertices[3]);
    drawLine(quad_vertices[3],quad_vertices[0]);

//    std::cout<<quad_vertices[0].y<<std::endl;
    BufferTri(quad_vertices[0], quad_vertices[1],quad_vertices[2]);
    BufferTri(quad_vertices[0], quad_vertices[3],quad_vertices[2]);
    
}

void XX::DrawTri(void)
{
    for(int i = 0; i<3; i++)
    {
        float vector[4][1] = {{tri_vertices[i].x},{tri_vertices[i].y},{tri_vertices[i].z},{tri_vertices[i].w}};
        ms->MultiMatrix4by1(vector);
        ms->DivideWComponent(vector);
        tri_vertices[i].x = vector[0][0];
        tri_vertices[i].y = vector[1][0];
        tri_vertices[i].z = vector[2][0];
        tri_vertices[i].w = vector[3][0];
    }
    ms->PushMatrix();
    ms->LoadIdentityMatrix();
    ms->ViewportMatrix(dimx, dimy);
    for(int i = 0; i<3; i++)
    {
        float vector[4][1] = {{tri_vertices[i].x},{tri_vertices[i].y},{tri_vertices[i].z},{tri_vertices[i].w}};
        ms->MultiMatrix4by1(vector);
        tri_vertices[i].x = vector[0][0];
        tri_vertices[i].y = vector[1][0];
        tri_vertices[i].z = vector[2][0];
        tri_vertices[i].w = vector[3][0];
    }
    ms->PopMatrix();
    drawLine(tri_vertices[0],tri_vertices[1]);
    drawLine(tri_vertices[1],tri_vertices[2]);
    drawLine(tri_vertices[2],tri_vertices[0]);
    
    BufferTri(tri_vertices[0], tri_vertices[1],tri_vertices[2]);
}

void XX::XXVertex3f(float x, float y, float z)
{
    
    if(VerticesRequired==4)
    {
        quad_vertices[VerticeNumber].x = x;
        quad_vertices[VerticeNumber].y = y;
        quad_vertices[VerticeNumber].z = z;
        quad_vertices[VerticeNumber].w = 1;
        VerticeNumber++;
        if(VerticeNumber==VerticesRequired)
        {DrawQuad();VerticeNumber=0;}
    }
    
    
    if(VerticesRequired==3)
    {
        tri_vertices[VerticeNumber].x = x;
        tri_vertices[VerticeNumber].y = y;
        tri_vertices[VerticeNumber].z = z;
        tri_vertices[VerticeNumber].w = 1;
        VerticeNumber++;
        if(VerticeNumber==VerticesRequired){DrawTri();VerticeNumber=0;}
    }
    
    
}

void XX::XXBegin(int form)
{
    if(form==0)
    {
        VerticesRequired = 3;
    }
    
    if(form==1)
    {
        VerticesRequired = 4;
    }
    VerticeNumber = 0;
}

bool XX::getBuffer(int x, int y)
{
    return buffer[y][x];
}

void XX::ClearBuffer(void)
{
    for(int j = 0; j<dimy; j++)
    {
        for(int i = 0; i<dimx; i++){buffer[j][i] = 0;}
        for(int i = 0; i<dimx; i++){z_buffer[j][i] = -1000.0;}
    }
}

void XX::XXEnd()
{
    
}







