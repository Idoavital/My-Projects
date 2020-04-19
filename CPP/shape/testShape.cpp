/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <unistd.h> /*sleep*/
#include <complex>
#include <iostream> //tan

#include "shapes.hpp"
using namespace ilrd;

/**********group 1*****************/
/* triangle 1*/
 Point p1(100,100);
 Point p2(300,100);
 Point p3(200,250);
 
 Point p4(200,150); 
 
 Point p5(200,150);
 /* triangle 2*/
 Point p7(100,200);
 Point p8(300,200);
 Point p9(200,50);
 Point mid(500,500);
 /**********group 2*****************/
 
 Point p2_1(300,100);
 Point p2_2(600,100);
 Point p2_3(450,250);
 
 Point p2_4(450,150);
 Point p2_5(450,150);
 
/****************************/
Circle c1(COLOR_RED ,p4,100 );
Triangle t1 (COLOR_RED ,p1 , p2 ,p3);
Triangle t2 (COLOR_YELLOW ,p7 , p8 ,p9); 
Rectangle r1(COLOR_BLUE ,p5 , 250 ,250);
 

 /**********group 2*****************/
Triangle t3 (COLOR_RED ,p2_1 , p2_2 ,p2_3);
Rectangle r2(COLOR_BLUE ,p2_4 , 250 ,250);


Group g1(p5);
Group g2(p2_5);
Group g_all(mid);

void DrawFunction();
int TimerFunction();


int main (int argc , char * argv[])
{
    g1.AddShape (c1);
    g1.AddShape (t1);
    g1.AddShape (r1);
    g1.AddShape (t2);
    
    g2.AddShape (t3);
    g2.AddShape (r2);
    
    g_all.AddShape (g2);
    g_all.AddShape (g1);
  
     DrawInit(argc, argv, 1500, 2000, DrawFunction);
     DrawSetTimerFunc(TimerFunction, 100);
     DrawMainLoop();
}

void DrawFunction()
{
  
  //g2.Draw ();
  //g2.Rotate (5);
  //g2.Step (3,2);
  
  //g1.Draw ();
  //g1.Step (4, 3);
  //g1.Rotate (5);
  
  g_all.Draw ();
  g_all.Rotate (5);
  

}

int TimerFunction()
{
  float x=0;
  float y=0;
    x += 5;
    y += 5;
    //sleep(1);
    return 1;  
}
