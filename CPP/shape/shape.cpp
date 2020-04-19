/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   shape.cpp
 * Author: ido
 *
 * Created on February 1, 2018, 10:51 AM
 */

#include <complex> //tan
#include <cstdlib>
#include "shapes.hpp"

#define PI 3.14159265

namespace ilrd
{

  inline Point MidTriangle(const Point& p1 ,const Point& p2 ,const Point& p3) 
  {
    int t_x = (p1.GetX()+ p2.GetX() + p3.GetX ())/3 ; 
    int t_y = (p1.GetY()+ p2.GetY() + p3.GetY ())/3 ; 
    Point p_ret (t_x , t_y );
    
    return p_ret;
  }
  
 /***********************class point *******************************/
  
Point::Point (int x_ , int y_) :m_x(x_), m_y(y_){}
int Point::GetX() const
{
  return (m_x);
} 
int Point::GetY() const
{
  return (m_y);
}
void Point::SetX(int x)
{
  m_x =x;
}
void Point::SetY(int y)
{
  m_y =y;
}

 Point Point::revolve (const Point& base ,float angle)
{
   Point t_p;
  float new_x = 0;
  float new_y = 0;
  float x = this->m_x - base.m_x;
  float y = this->m_y - base.m_y;
  
  new_x = ( (x * cos (angle * PI / 180)) - (y * sin(angle * PI / 180 )) );
  new_y = ( (x * sin (angle * PI / 180)) + (y * cos (angle * PI / 180)) );
  
  t_p.m_x = new_x + base.m_x ;
  t_p.m_y = new_y + base.m_y ;
  
  return t_p;
}
 /***********************class shape *******************************/

  Shape::Shape(const Point& base ,COLORS color ) :
                                m_base_point(base), m_color(color){}
          
  Shape::~Shape(){}
   
  void Shape::Step(int move_on_x_axis, int move_on_y_axis)
  {
    int t_x = m_base_point.GetX() +move_on_x_axis;
    int t_y = m_base_point.GetY() +move_on_y_axis;
    
    m_base_point.SetX(t_x);
    m_base_point.SetY(t_y);
    
  }
void Shape::Rotate(float angle)
{
}
   
COLORS Shape::GetColor()
{
  return m_color;
}
void Shape::SetColor(COLORS c)
{
  m_color = c;
}
 Point Shape::GetPiont()
 {
   return m_base_point;
 }
 
 void Shape::SetPiont(Point p1)
 {
   m_base_point.SetX (p1.GetX ());
   m_base_point.SetY (p1.GetY ());

 }
        
/***********************class Circle *******************************/
Circle::Circle(COLORS color, const Point &base, int radius): 
                            Shape(base , color), m_radius(radius){}

void Circle::Draw()
{
     DrawCircle(this->GetColor (), m_base_point.GetX (),m_base_point.GetY (), m_radius);
}

/***********************class Triangle *******************************/
Triangle:: Triangle(COLORS color, const Point& top, const Point& base_left,
                     const Point& base_right): Shape(MidTriangle(top ,base_left,base_right ), color )
                           ,m_angle(0)

{
  //set relative points from base point.
  m_base_top.SetX (top.GetX () - this->m_base_point.GetX ());
  m_base_top.SetY (top.GetY () - this->m_base_point.GetY ());
  
  m_base_left.SetX (base_left.GetX () - this->m_base_point.GetX ());
  m_base_left.SetY (base_left.GetY () - this->m_base_point.GetY ());
  
  m_base_right.SetX (base_right.GetX () - this->m_base_point.GetX ());
  m_base_right.SetY (base_right.GetY () - this->m_base_point.GetY ());
   
}

void Triangle::Draw()
{
    /* temp points of the three corner of the triangle */
    Point p1 (m_base_top.GetX ()+m_base_point.GetX (), m_base_top.GetY() +m_base_point.GetY() );
    Point p2 (m_base_left.GetX ()+m_base_point.GetX (), m_base_left.GetY() +m_base_point.GetY() );
    Point p3 (m_base_right.GetX ()+m_base_point.GetX (), m_base_right.GetY() +m_base_point.GetY() );
 
 
    p1 = p1.revolve  (m_base_point ,m_angle);
    p2 = p2.revolve ( m_base_point ,m_angle);
    p3 = p3.revolve  (m_base_point ,m_angle);
    DrawPolygon(this->GetColor (), 3 ,p1.GetX ()  ,p1.GetY ()
                                ,p2.GetX (), p2.GetY ()
                                ,p3.GetX (), p3.GetY ());
            
      
}

void Triangle::Rotate(float angle)
{
  m_angle +=angle;
  
}
/***********************class Rectangle *******************************/

Rectangle::Rectangle(COLORS color, const Point &base, int width, int height): Shape(base , color),
                m_width(width),m_height (height),m_angle (0)
{
  /* set 4 corner point */
  
  m_a_corner.SetX (0);
  m_a_corner.SetY (0);
  
  m_b_corner.SetX (0);
  m_b_corner.SetY (height);
  
  m_c_corner.SetX (width);
  m_c_corner.SetY (height);
    
  m_d_corner.SetX (width);
  m_d_corner.SetY (0);
  
}

void Rectangle::Draw()
{
  /* relative for the base */
  int t_x = this->m_base_point.GetX () - (m_width/ 2 );
  int t_y = this->m_base_point.GetY () -  (m_height/ 2);
  
  Point p1 ( m_a_corner.GetX()+ t_x ,m_a_corner.GetY () + t_y);
  Point p2 ( m_b_corner.GetX()+ t_x ,m_b_corner.GetY () + t_y);
  Point p3 ( m_c_corner.GetX()+ t_x ,m_c_corner.GetY () + t_y);
  Point p4 ( m_d_corner.GetX()+ t_x ,m_d_corner.GetY () + t_y);

    /*calc the poistion relative to base and to the base*/
  p1 = p1.revolve (m_base_point ,m_angle );
  p2 = p2.revolve ( m_base_point , m_angle );
  p3 = p3.revolve ( m_base_point , m_angle );
  p4 = p4.revolve ( m_base_point , m_angle );

  DrawPolygon(this->GetColor () ,4 ,p1.GetX (), p1.GetY ()
                            ,p2.GetX (), p2.GetY ()
                            ,p3.GetX (), p3.GetY ()
                            ,p4.GetX (), p4.GetY ());

    
}
void Rectangle::Rotate(float angle) 
{
  m_angle +=angle;

}

 /***********************class point *******************************/
Group::Group(const Point &position):Shape(position),m_mem_size(0)
{
}

Group& Group::AddShape(const Shape& shape)
{

  m_list[m_mem_size]=const_cast<Shape*> (&shape);
  m_mem_size++;
  return *this;
}
void Group::Draw()
{
  
  for (int i =0; i<m_mem_size; i++)
    {
      m_list[i]->Draw ();
    }
}
void Group::Rotate(float angle)
{
 
  int i = 0;
  Point p1;
  Point p2;


   for ( i = 0; i<m_mem_size; i++)
    {
      p1=m_list[i]->GetPiont ();
      p2 = p1.revolve (m_base_point , angle);
      m_list[i]->SetPiont (p2);
      m_list[i]->Rotate(angle);
      m_list[i]->SetPiont (p1);
     
    }
}

void Group::Step(int move_on_x_axis, int move_on_y_axis)
{
   m_base_point.SetX (m_base_point.GetX ()+ move_on_x_axis);
   m_base_point.SetY (m_base_point.GetY ()+ move_on_x_axis);
   
   int i = 0;
   for ( i = 0; i<m_mem_size; i++)
    {
       m_list[i]->Step( move_on_x_axis,  move_on_y_axis);
    }
}


}


