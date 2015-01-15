//
//  main.cpp
//  opengl
//
//  Created by xinglunxu on 12/6/14.
//
//
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include "MatrixStack.h"
#include "XX.h"
#include <time.h>
#include <sys/stat.h>

float turn_angles = 0;
float interval = 5;
float number1 = 0;
float number2 = 0;
float number3 = 0;
float number4 = 0;
float number5 = 0;
float number6 = 0;
float number7 = 0;
float number8 = 0;
float number9 = 0;
const int GL_QUADS=1;
const int GL_TRIANGLES=0;
int counter=0;

MatrixStack ms;
XX xx(&ms);

void drawBar(float angle, float x, float y, float z)
{
    ms.PushMatrix();
    ms.Rotate(angle,x,y,z);
    ms.Translate(0,0,0.5);
    xx.XXBegin(GL_QUADS);
    
    xx.XXVertex3f(-0.6, 0.6, 0);
    xx.XXVertex3f(0.6, 0.6, 0);
    xx.XXVertex3f(0.6, 0.5, 0);
    xx.XXVertex3f(-0.6, 0.5, 0);
    
    xx.XXVertex3f(-0.6, 0.6, 0.1);
    xx.XXVertex3f(0.6, 0.6, 0.1);
    xx.XXVertex3f(0.6, 0.5, 0.1);
    xx.XXVertex3f(-0.6, 0.5, 0.1);
    
    xx.XXVertex3f(-0.6, 0.6, 0.1);
    xx.XXVertex3f(0.6, 0.6, 0.1);
    xx.XXVertex3f(0.6, 0.6, 0);
    xx.XXVertex3f(-0.6, 0.6, 0);
    
    xx.XXVertex3f(-0.6, 0.5, 0.1);
    xx.XXVertex3f(0.6, 0.5, 0.1);
    xx.XXVertex3f(0.6, 0.5, 0);
    xx.XXVertex3f(-0.6, 0.5, 0);
    
    xx.XXEnd();
    ms.PopMatrix();
}

void drawBarAroundCube()
{
    drawBar(0,0,0,0);
    drawBar(90,1,0,0);
    drawBar(180,1,0,0);
    drawBar(270,1,0,0);
    
    ms.PushMatrix();
    ms.Rotate(90,0,1,0);
    drawBar(0,0,0,0);
    drawBar(90,0,0,1);
    drawBar(180,0,0,1);
    drawBar(270,0,0,1);
    ms.PopMatrix();
    
    ms.PushMatrix();
    ms.Rotate(90,0,0,1);
    drawBar(0,0,0,0);
    drawBar(90,0,1,0);
    drawBar(180,0,1,0);
    drawBar(270,0,1,0);
    
    ms.PopMatrix();
}

void drawFace(float angle, float x, float y, float z)
{
    ms.PushMatrix();
    ms.Rotate(angle,x,y,z);
    ms.Translate(0.0f,0.0f,0.5f);
    xx.XXBegin(GL_QUADS);

    xx.XXVertex3f( -0.5f, 0.5f, 0.0f);
    xx.XXVertex3f(0.5f, 0.5f, 0.0f);
    xx.XXVertex3f(0.5f, -0.5f, 0.0f);
    xx.XXVertex3f( -0.5f, -0.5f, 0.0f);
    
    xx.XXEnd();
    ms.PopMatrix();
}

void drawFaceAroundCube()
{
    drawFace(270,1,0,0);
    drawFace(0.0, 0.0, 1, 0.0);
    drawFace(90,0,1,0);
    drawFace(180,0,1,0);
    drawFace(270,0,1,0);
    drawFace(90, 1,0,0);
}

void drawTri(float depth)
{
    ms.PushMatrix();
    
    ms.Translate(0,0,0.5);
    
    xx.XXBegin(GL_QUADS);
    xx.XXVertex3f(0, 0.3, depth);
    xx.XXVertex3f(0, 0.3, 0);
    xx.XXVertex3f(0.3, -0.3, 0);
    xx.XXVertex3f(0.3, -0.3, depth);
    xx.XXEnd();
    
    xx.XXBegin(GL_QUADS);
    xx.XXVertex3f(0, 0.3, depth);
    xx.XXVertex3f(0, 0.3, 0);
    xx.XXVertex3f(-0.3, -0.3, 0);
    xx.XXVertex3f(-0.3, -0.3, depth);
    xx.XXEnd();
    
    xx.XXBegin(GL_QUADS);
    xx.XXVertex3f(-0.3, -0.3, depth);
    xx.XXVertex3f(-0.3, -0.3, 0);
    xx.XXVertex3f(0.3, -0.3, 0);
    xx.XXVertex3f(0.3, -0.3, depth);
    xx.XXEnd();
    
    ms.Translate(0,0,depth);
    
    xx.XXBegin(GL_TRIANGLES);
    xx.XXVertex3f(0,0.3,0);
    xx.XXVertex3f(0.3,-0.3,0);
    xx.XXVertex3f(-0.3,-0.3,0);
    xx.XXEnd();
    
    ms.PopMatrix();
    
}

void drawTriForCir(float r_, float d, float depth)
{
    
    xx.XXBegin(GL_TRIANGLES);
    xx.XXVertex3f(0,0,depth);
    xx.XXVertex3f(r_,d,depth);
    xx.XXVertex3f(r_,-d,depth);
    xx.XXEnd();
    
    xx.XXBegin(GL_QUADS);
    
    xx.XXVertex3f(0,0,0);
    xx.XXVertex3f(0,0,depth);
    xx.XXVertex3f(r_,d,depth);
    xx.XXVertex3f(r_,d,0);
    
    xx.XXVertex3f(0,0,0);
    xx.XXVertex3f(0,0,depth);
    xx.XXVertex3f(r_,-d,depth);
    xx.XXVertex3f(r_,-d,0);
    
    xx.XXVertex3f(r_,d,0);
    xx.XXVertex3f(r_,d,depth);
    xx.XXVertex3f(r_,-d,depth);
    xx.XXVertex3f(r_,-d,0);
    xx.XXEnd();
}

void drawCir(float r, float depth)
{
    float d = sin(0.5*PI/180)*r;
    float r_ = cos(0.5*PI/180)*r;
    ms.PushMatrix();
    ms.Translate(0,0,0.5);
    for(int i = 0; i<361; i++)
    {
        
        drawTriForCir(r_,d,depth);
        ms.Rotate(1,0,0,1);
    }
    ms.PopMatrix();
}

void drawPenta()
{
    ms.PushMatrix();
    ms.Translate(0,0,0.5);
    
    xx.XXBegin(GL_TRIANGLES);
    
    xx.XXVertex3f(0,0.4,0.1);
    xx.XXVertex3f(0.4,0.15,0.1);
    xx.XXVertex3f(0.2,-0.2,0.1);
    
    xx.XXVertex3f(0,0.4,0.1);
    xx.XXVertex3f(-0.4,0.15,0.1);
    xx.XXVertex3f(-0.2,-0.2,0.1);
    
    xx.XXVertex3f(0,0.4,0.1);
    xx.XXVertex3f(0.2,-0.2,0.1);
    xx.XXVertex3f(-0.2,-0.2,0.1);
    
    xx.XXEnd();
    
    xx.XXBegin(GL_QUADS);
    xx.XXVertex3f(0,0.4,0);
    xx.XXVertex3f(0,0.4,0.1);
    xx.XXVertex3f(0.4,0.15,0.1);
    xx.XXVertex3f(0.4,0.15,0);
    
    xx.XXVertex3f(0,0.4,0);
    xx.XXVertex3f(0,0.4,0.1);
    xx.XXVertex3f(-0.4,0.15,0.1);
    xx.XXVertex3f(-0.4,0.15,0);
    
    xx.XXVertex3f(0.4,0.15,0);
    xx.XXVertex3f(0.4,0.15,0.1);
    xx.XXVertex3f(0.2,-0.2,0.1);
    xx.XXVertex3f(0.2,-0.2,0);
    
    xx.XXVertex3f(-0.4,0.15,0);
    xx.XXVertex3f(-0.4,0.15,0.1);
    xx.XXVertex3f(-0.2,-0.2,0.1);
    xx.XXVertex3f(-0.2,-0.2,0);
    
    xx.XXVertex3f(0.2,-0.2,0);
    xx.XXVertex3f(0.2,-0.2,0.1);
    xx.XXVertex3f(-0.2,-0.2,0.1);
    xx.XXVertex3f(-0.2,-0.2,0);
    
    xx.XXEnd();
    
    ms.PopMatrix();
}

void drawCuboid(float l, float w, float h)
{
    
    xx.XXBegin(GL_QUADS);
    
    xx.XXVertex3f(l/2,h/2,0);
    xx.XXVertex3f(l/2,-h/2,0);
    xx.XXVertex3f(-l/2,-h/2,0);
    xx.XXVertex3f(-l/2,h/2,0);
    
    xx.XXVertex3f(l/2,h/2,w);
    xx.XXVertex3f(l/2,-h/2,w);
    xx.XXVertex3f(-l/2,-h/2,w);
    xx.XXVertex3f(-l/2,h/2,w);
    
    xx.XXVertex3f(l/2,h/2,0);
    xx.XXVertex3f(l/2,h/2,w);
    xx.XXVertex3f(l/2,-h/2,w);
    xx.XXVertex3f(l/2,-h/2,0);
    
    xx.XXVertex3f(-l/2,h/2,0);
    xx.XXVertex3f(-l/2,h/2,w);
    xx.XXVertex3f(-l/2,-h/2,w);
    xx.XXVertex3f(-l/2,-h/2,0);
    
    xx.XXVertex3f(-l/2,h/2,0);
    xx.XXVertex3f(-l/2,h/2,w);
    xx.XXVertex3f(l/2,h/2,w);
    xx.XXVertex3f(l/2,h/2,0);
    
    xx.XXVertex3f(-l/2,-h/2,0);
    xx.XXVertex3f(-l/2,-h/2,w);
    xx.XXVertex3f(l/2,-h/2,w);
    xx.XXVertex3f(l/2,-h/2,0);
    
    xx.XXEnd();
    
}

void drawH()
{
    ms.PushMatrix();
    
    ms.Translate(0,0,0.5);
    
    drawCuboid(0.6,0.1,0.09);
    
    ms.PushMatrix();
    ms.Translate(0.3,0,0);
    drawCuboid(0.06,0.1,0.7);
    ms.PopMatrix();
    
    ms.PushMatrix();
    ms.Translate(-0.3,0,0);
    drawCuboid(0.06,0.1,0.7);
    ms.PopMatrix();
    
    ms.PopMatrix();
}

void drawA()
{
    ms.PushMatrix();
    ms.Translate(0,0,0.5);
    drawCuboid(0.3,0.1,0.09);
    
    ms.PushMatrix();
    ms.Translate(0.16,0,0);
    ms.Rotate(30,0,0,1);
    drawCuboid(0.06,0.1,0.7);
    ms.PopMatrix();
    
    ms.PushMatrix();
    ms.Translate(-0.16,0,0);
    ms.Rotate(-30,0,0,1);
    drawCuboid(0.06,0.1,0.7);
    ms.PopMatrix();
    
    ms.PopMatrix();
}

void drawPartForHCir(float r_, float d, float depth)
{
    xx.XXBegin(GL_QUADS);
    
    xx.XXVertex3f(r_-d,d,0);
    xx.XXVertex3f(r_+d,d,0);
    xx.XXVertex3f(r_+d,-d,0);
    xx.XXVertex3f(r_-d,-d,0);
    
    xx.XXVertex3f(r_-d,d,depth);
    xx.XXVertex3f(r_+d,d,depth);
    xx.XXVertex3f(r_+d,-d,depth);
    xx.XXVertex3f(r_-d,-d,depth);
    
    xx.XXVertex3f(r_-d,d,0);
    xx.XXVertex3f(r_-d,d,depth);
    xx.XXVertex3f(r_+d,d,depth);
    xx.XXVertex3f(r_+d,d,0);
    
    xx.XXVertex3f(r_-d,-d,0);
    xx.XXVertex3f(r_-d,-d,depth);
    xx.XXVertex3f(r_+d,-d,depth);
    xx.XXVertex3f(r_+d,-d,0);
    
    xx.XXVertex3f(r_-d,d,0);
    xx.XXVertex3f(r_-d,d,depth);
    xx.XXVertex3f(r_-d,-d,depth);
    xx.XXVertex3f(r_-d,-d,0);
    
    xx.XXVertex3f(r_+d,d,0);
    xx.XXVertex3f(r_+d,d,depth);
    xx.XXVertex3f(r_+d,-d,depth);
    xx.XXVertex3f(r_+d,-d,0);
    
    xx.XXEnd();
    
}

void drawHCir(float R, float r, float g, float b, float depth,float size, float angle)
{
    float d = sin(0.5*PI/180)*R*size;
    float r_ = cos(0.5*PI/180)*R;
    ms.PushMatrix();
    for(int i=0; i<angle; i++)
    {
        drawPartForHCir(r_, d, depth);
        ms.Rotate(1,0,0,1);
    }
    
    ms.PopMatrix();
}

void drawCube(float angle, float x, float y, float z, float x_, float y_, float z_)
{
    ms.PushMatrix();
    ms.Translate(x_,y_,z_);
    ms.Rotate(angle,x,y,z);
    drawFaceAroundCube();
    drawBarAroundCube();
    
    
    drawTri(0.1);
    
    ms.PushMatrix();
    ms.Rotate(90, 0,1,0);
    drawCir(0.35,0.1);
    ms.Rotate(90, 0,1,0);
    drawPenta();
    ms.Rotate(90,0,1,0);
    drawH();
    ms.PopMatrix();
    
    ms.Rotate(270,1,0,0);
    drawA();
    
    ms.Rotate(180,1,0,0);
    ms.Rotate(40,0,0,1);
    ms.Translate(0,0,0.5);
    drawHCir(0.4,0.9,0.3,0,0.1,10,270);
    
    ms.PopMatrix();
    
}

void draw1()
{
    drawCuboid(0.2, 0.1, 0.8);
    
    ms.PushMatrix();
    ms.Translate(0,-0.4,0);
    drawCuboid(0.5,0.1,0.1);
    ms.PopMatrix();
    
    ms.PushMatrix();
    ms.Rotate(35,0,0,1);
    ms.Translate(0,0.325,0);
    drawCuboid(0.3,0.1,0.1);
    ms.PopMatrix();
    
}

void draw2()
{
    ms.PushMatrix();
    ms.Translate(0,-0.4,0);
    drawCuboid(0.5,0.1,0.1);
    ms.PopMatrix();
    
    ms.PushMatrix();
    ms.Translate(0,-0.2,0);
    ms.Rotate(45,0,0,1);
    drawCuboid(0.5,0.1,0.1);
    ms.PopMatrix();
    
    ms.PushMatrix();
    drawHCir(0.2, 0.3,0,0.6, 0.15, 10,180);
    ms.PopMatrix();
}

void draw3()
{
    ms.PushMatrix();
    ms.Translate(0,0.18,0);
    ms.Rotate(-120,0,0,1);
    drawHCir(0.2, 0,0.1,0.6, 0.15, 10,240);
    ms.PopMatrix();
    
    ms.PushMatrix();
    ms.Translate(0,-0.2,0);
    ms.Rotate(-120,0,0,1);
    drawHCir(0.2, 0,0.1,0.6, 0.15, 10,240);
    ms.PopMatrix();
}

void draw4()
{
    drawCuboid(0.5,0.1,0.07);
    drawCuboid(0.07,0.1,0.6);
    
    ms.PushMatrix();
    ms.Rotate(45, 0,0,1);
    ms.Translate(0,0.2,0);
    drawCuboid(0.4,0.1,0.05);
    ms.PopMatrix();
}

void draw5()
{
    ms.PushMatrix();
    ms.Translate(0,-0.2,0);
    ms.Rotate(-120,0,0,1);
    drawHCir(0.2, 0.7,0.2,0, 0.15, 10,240);
    ms.PopMatrix();
    
    ms.PushMatrix();
    ms.Translate(-0.1, 0.1,0);
    drawCuboid(0.1,0.1,0.3);
    ms.PopMatrix();
    
    ms.PushMatrix();
    ms.Translate(0,0.2,0);
    drawCuboid(0.3,0.1,0.1);
    ms.PopMatrix();
}

void draw6()
{
    ms.PushMatrix();
    ms.Translate(0,-0.2,0);
    drawHCir(0.2, 0.7,0.2,0, 0.15, 10,360);
    ms.Translate(0.15,0,0);
    ms.Rotate(90,0,0,1);
    ms.Scale(1.3,1,1);
    drawHCir(0.4, 0.7,0.2,0, 0.1, 10,90);
    ms.PopMatrix();
}

void draw9()
{
    ms.PushMatrix();
    ms.Rotate(180,0,0,1);
    ms.Translate(0,-0.2,0);
    drawHCir(0.2, 0.7,0.2,0, 0.15, 10,360);
    ms.Translate(0.15,0,0);
    ms.Rotate(90,0,0,1);
    ms.Scale(1.3,1,1);
    drawHCir(0.4, 0.7,0.2,0, 0.1, 10,90);
    ms.PopMatrix();
}

void draw8()
{
    ms.PushMatrix();
    ms.Translate(0,0.18,0);
    drawHCir(0.2, 0,0.1,0.6, 0.15, 10,360);
    ms.PopMatrix();
    
    ms.PushMatrix();
    ms.Translate(0,-0.2,0);
    drawHCir(0.2, 0,0.1,0.6, 0.15, 10,360);
    ms.PopMatrix();
}

void draw7()
{
    ms.PushMatrix();
    ms.Translate(0,0.2,0);
    drawCuboid(0.4,0.1,0.1);
    ms.PopMatrix();
    
    ms.PushMatrix();
    ms.Rotate(-30, 0,0,1);
    ms.Translate(0.06,0,0);
    drawCuboid(0.1,0.1,0.6);
    ms.PopMatrix();
}

void drawNumbers()
{
    if(counter>interval && counter < interval*8)
    {
        ms.PushMatrix();
        ms.Translate(2-number1*0.1,0, number1*0.3);
        draw1();
        ms.PopMatrix();
        number1++;
    }

    if(counter>8*interval && counter < interval*15){
        ms.PushMatrix();
        ms.Translate(-2+number2*0.1,0, number2*0.3);
        draw2();
        ms.PopMatrix();
        number2++;
    }
    
    if(counter>15*interval && counter < interval*22)
    {
        ms.PushMatrix();
        ms.Translate(3-number3*0.15,0, 1+number3*0.03);
        draw3();
        ms.PopMatrix();
        number3++;
    }
    
    if(counter>22*interval && counter < interval*29)
    {
        ms.PushMatrix();
        ms.Translate(-3+number4*0.15,0, 1+number4*0.3);
        draw4();
        ms.PopMatrix();
        number4++;
    }
    
    if(counter>29*interval && counter < interval*36)
    {
        ms.PushMatrix();
        ms.Translate(2-number5*0.1,0, number5*0.3);
        draw5();
        ms.PopMatrix();
        number5++;
    }
    
    if(counter>36*interval && counter < interval*43){
        ms.PushMatrix();
        ms.Translate(-2+number6*0.1,0, number6*0.3);
        draw6();
        ms.PopMatrix();
        number6++;
    }
    
    if(counter>43*interval && counter < interval*50)
    {
        ms.PushMatrix();
        ms.Translate(3-number7*0.15,0, 1+number7*0.3);
        draw7();
        ms.PopMatrix();
        number7++;
    }
    
    if(counter>50*interval && counter < interval*57)
    {
        ms.PushMatrix();
        ms.Translate(-3+number8*0.15,0, 1+number8*0.3);
        draw8();
        ms.PopMatrix();
        number8++;
    }
    
    if(counter>57*interval && counter < interval*64)
    {
        ms.PushMatrix();
        ms.Translate(2-number9*0.1,0, number9*0.3);
        draw9();
        ms.PopMatrix();
        number9++;
    }
    
}



void drawTurningCubes()
{
    drawCube(20+turn_angles, 0, 1, 0, 1.5, 0, 1.5);
    drawCube(turn_angles,0,1,0,0,0,0);
    drawCube(10-turn_angles, 0, 1, 0, -1.5, 0, 1.5);
    drawCube(15-turn_angles, 0, 1, 0, 3, 0, 3);
    drawCube(15-turn_angles, 0, 1, 0, -3, 0, 3);
}

void ChangeName(char *name)
{
    int one, two, three, four, five;
    one = counter%10;
    two = (counter%100-one)/10;
    three = (counter%1000-two)/100;
    four = (counter%10000-three)/1000;
    five = (counter%100000-four)/10000;
    name[40] = 48+five;
    name[41] = 48+four;
    name[42] = 48+three;
    name[43] = 48+two;
    name[44] = 48+one;
}

void writePPM()
{
    char name[] ="/Users/xinglunxu/opgl/opengl/video/first00000.ppm";//40~
    ChangeName(name);
    int i, j;
    FILE *fp = fopen(name, "wb"); /* b - binary mode */
    (void) fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
    for (j = 0; j < dimy; ++j)
    {
        for (i = 0; i < dimx; ++i)
        {
            static unsigned char color[3];
            if(xx.getBuffer(i,j)){
                color[0] = 0;  /* red */
                color[1] = 0;  /* green */
                color[2] = 0;  /* blue */
            }
            else
            {
                color[0] = 255;  /* red */
                color[1] = 255;  /* green */
                color[2] = 255;  /* blue */
            }
            (void) fwrite(color, 1, 3, fp);
        }
    }

    (void) fclose(fp);
    char newname[] ="/Users/xinglunxu/opgl/opengl/video/first00000.jpeg";
    for(int i = 40; i<45; i++)
    {
        newname[i] = name[i];
    }
    rename( name , newname );

}

void MainLoop()
{
    fflush(stdout);
    ms.LoadIdentityMatrix();
    ms.PerspectiveProjectionMatrix(-1, 1, 1, -1, 2, 15);
    ms.LookAtMatrix(0+counter*0.02,2+counter*0.01,12, 0,0,0, 0,1,0);
    drawTurningCubes();
    drawNumbers();
    writePPM();
    xx.ClearBuffer();
    counter++;
    turn_angles+=2;
}

int main(void)
{
    std::cout<<"This program will generate a total of 330 pictures to the video folder and it takes about two minutes :)"<<std::endl;
    mkdir("/Users/xinglunxu/opgl/opengl/video", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    while(counter<330)
    {
        MainLoop();
        
    }
    return EXIT_SUCCESS;
}


