//
//  MatrixStack.h
//  opengl
//
//  Created by xinglunxu on 12/8/14.
//
//

#ifndef __opengl__MatrixStack__
#define __opengl__MatrixStack__

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <math.h>

const float PI = 3.1415926;
struct MatrixNode{float (*matrix)[4]; MatrixNode* next;};


class MatrixStack{
private:
    MatrixNode* current;
public:
    void MultiMatrix4by4OnRight(float matrix[][4]);
    void MultiMatrix4by1(float vector[][1]);
    void DivideWComponent(float vector[][1]);
    void PrintCurrentMatrix(void);
    void LoadIdentityMatrix(void);
    void ViewportMatrix(float width, float height);
    void PerspectiveProjectionMatrix(float, float, float, float,float,float);
    void LookAtMatrix(float,float,float,float,float,float,float,float,float);
    void PushMatrix(void);
    void PopMatrix(void);
    void Translate(float, float, float);
    void Rotate(float, float, float, float);
    void Scale(float, float, float);
    MatrixStack();
};





#endif /* defined(__opengl__MatrixStack__) */
