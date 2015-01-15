//
//  MatrixStack.cpp
//  opengl
//
//  Created by xinglunxu on 12/8/14.
//
//

#include "MatrixStack.h"

void MatrixStack::MultiMatrix4by4OnRight(float matrix[][4])
{
    float (*NewMatrix)[4] = new float[4][4];
    for(int i=0; i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            NewMatrix[i][j]=0;
            for(int k=0; k<4;k++){NewMatrix[i][j] += current->matrix[i][k]*matrix[k][j];}
        }
    }
    delete[] current->matrix;
    current->matrix = NewMatrix;
}

void MatrixStack::MultiMatrix4by1(float vector[][1])
{
    float NewVector[4][1];
    for(int i=0; i<4;i++)
    {
        NewVector[i][0] = 0;
        for(int j=0;j<4;j++)
        {
            NewVector[i][0] += current->matrix[i][j]*vector[j][0];
        }
    }
    for(int i = 0; i<4; i++)
    {
        vector[i][0] = NewVector[i][0];
    }
}

void MatrixStack::DivideWComponent(float vector[][1])
{
    vector[0][0] = vector[0][0]/vector[3][0];
    vector[1][0] = vector[1][0]/vector[3][0];
    vector[2][0] = vector[2][0]/vector[3][0];
    vector[3][0] = 1;
}

void MatrixStack::PrintCurrentMatrix()
{
    for(int i=0; i<4;i++)
    {
        std::cout<<i<<" row: ";
        for(int j=0;j<4;j++)
        {
            std::cout<<current->matrix[i][j]<<" - ";
        }
        std::cout<<std::endl;
    }
    
}

void MatrixStack::LoadIdentityMatrix()
{
    delete[] current->matrix;
    current->matrix = new float[4][4];
    for(int i=0; i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(i == j){current->matrix[i][j]=1;}
            else{current->matrix[i][j]=0;}
        }
    }
}

MatrixStack::MatrixStack()
{
    current = new MatrixNode;
    current->matrix = new float[4][4];
    for(int i=0; i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(i == j){current->matrix[i][j]=1;}
            else{current->matrix[i][j]=0;}
        }
    }
}

void MatrixStack::ViewportMatrix(float width, float height)
{
    float v[4][4] = {{width/2,0,0,0},{0,height/2,0,0},{0,0,1,0},{0,0,0,1}};
    MultiMatrix4by4OnRight(v);
}
void MatrixStack::PerspectiveProjectionMatrix(float l, float r, float t, float b,float n,float f)
{
  float p[4][4] =
    {{2*n/(r-l),0,(r+l)/(l-r),0},
    {0,2*n/(t-b),(t+b)/(b-t),0},
    {0,0,(f+n)/(n-f),2*n*f/(f-n)},
    {0,0,1,0}};
    
  MultiMatrix4by4OnRight(p);
}



void MatrixStack::LookAtMatrix(float Ex,float Ey,float Ez,float Px,float Py,float Pz, float UPx,float UPy,float UPz)
{
    float Dx, Dy, Dz, Dlength, Sx, Sy, Sz, Slength, Ux, Uy, Uz, Ulength;
        Dx = Px - Ex; Dy = Py - Ey; Dz = Pz - Ez;
    Dlength = sqrt(pow(Dx,2)+pow(Dy,2)+pow(Dz,2));
    Dx = Dx/Dlength; Dy = Dy/Dlength; Dz=Dz/Dlength;

    Sx = Dy*UPz-Dz*UPy; Sy = Dz*UPx-Dx*UPz; Sz = Dx*UPy - Dy*UPx;
    Slength = sqrt(pow(Sx,2)+pow(Sy,2)+pow(Sz,2));
    Sx = Sx/Slength; Sy = Sy/Slength; Sz = Sz/Slength;

    Ux = Sy*Dz-Sz*Dy; Uy = Sz*Dx-Sx*Dz; Uz = Sx*Dy-Sy*Dx;
    Ulength = sqrt(pow(Ux,2)+pow(Uy,2)+pow(Uz,2));
    Ux = Ux/Ulength; Uy = Uy/Ulength; Uz = Uz/Ulength;
    
    float m[4][4] = {{Sx,Sy,Sz,0},{Ux,Uy,Uz,0},{Dx,Dy,Dz,0},{0,0,0,1}};
    float t[4][4] = {{1,0,0,-Ex},{0,1,0,-Ey},{0,0,1,-Ez},{0,0,0,1}};
    MultiMatrix4by4OnRight(m);
    MultiMatrix4by4OnRight(t);
    
}

void MatrixStack::PushMatrix()
{
    MatrixNode* NewNode = new MatrixNode();
    NewNode->matrix = new float[4][4];
    for(int i=0; i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            NewNode->matrix[i][j] = current->matrix[i][j];
        }
    }
    NewNode->next = current;
    current = NewNode;
}

void MatrixStack::PopMatrix()
{
    MatrixNode* temp = current->next;
    delete[] current->matrix;
    delete current;
    current = temp;
}

void MatrixStack::Translate(float x, float y, float z)
{
    float T[4][4] = {{1,0,0,x},{0,1,0,y},{0,0,1,z},{0,0,0,1}};
    MultiMatrix4by4OnRight(T);
}

void MatrixStack::Rotate(float angle, float x, float y, float z)
{
    float a = angle*PI/180;
    float rx[4][4] = {{1,0,0,0},{0,cos(a),-sin(a),0},
                      {0,sin(a),cos(a),0},{0,0,0,1}};
    float ry[4][4] = {{cos(a),0,sin(a),0},{0,1,0,0},
                      {-sin(a),0,cos(a),0},{0,0,0,1}};
    float rz[4][4] = {{cos(a),-sin(a),0,0},{sin(a),cos(a),0,0},{0,0,1,0},{0,0,0,1}};
    if(x==1){MultiMatrix4by4OnRight(rx);}
    if(y==1){MultiMatrix4by4OnRight(ry);}
    if(z==1){MultiMatrix4by4OnRight(rz);}
}

void MatrixStack::Scale(float a, float b, float c)
{
    float s[4][4] = {{a,0,0,0},{0,b,0,0},{0,0,c,0},{0,0,0,1}};
    MultiMatrix4by4OnRight(s);
}




