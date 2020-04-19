/* 
 * File:   shapes.hpp
 * Author: ido
 *
 * Created on January 31, 2018, 6:29 PM
 */

#ifndef __SHAPES_HPP__
#define __SHAPES_HPP__

#include <cstddef>


#include "glut_utils.h"


namespace ilrd {

    class Point {
    public:

        explicit Point(int x_ = 0, int y_ = 0);
         
        //generated function : copy operator=, CCtor, Dtor

        int GetX() const;
        int GetY() const;

        void SetX(int x);
        void SetY(int y);
        
        //revolve
        Point revolve (const Point& base ,float angle);
    private:

        int m_x;
        int m_y;
    };

    /**************************************************************************/

    class Shape {
    public:

        Shape(const Point& base ,COLORS color = COLOR_RED);
        virtual ~Shape();

        virtual void Step(int move_on_x_axis, int move_on_y_axis);
        virtual void Rotate(float angle);
        virtual void Draw() = 0;

        COLORS GetColor();
        void SetColor(COLORS c);
        
        Point GetPiont();
        void SetPiont(Point p1);
    protected:
        
        Point m_base_point;

    private:
       
        COLORS m_color;
    };

    /**************************************************************************/

    class Circle : public Shape {
    public:

        Circle(COLORS color, const Point &base, int radius = 5);

        void Rotate(int angle);
        void Draw();

    private:

        int m_radius;
    };

    /**************************************************************************/

    class Triangle : public Shape {
    public:

        Triangle(COLORS color, const Point& top, const Point& base_left, const Point& base_right);
        void Rotate(float angle);
        void Draw();

    private:

        Point m_base_top;
        Point m_base_left;
        Point m_base_right;
        int m_angle;
       

    };

    /**************************************************************************/

    class Rectangle : public Shape {
    public:

        Rectangle(COLORS color, const Point &corner, int width, int height);
        
        void Rotate(float angle) ;
        void Draw();

    private:
        
        Point m_a_corner;
        Point m_b_corner;
        Point m_c_corner;
        Point m_d_corner;

        int m_width;
        int m_height;
        int m_angle;

    };

    /**************************************************************************/

    class Group : public Shape {
        
    public:
        
        explicit Group(const Point &position);
        
        Group& AddShape(const Shape& shape);
        void Draw();
        void Rotate(float angle);
       void Step(int move_on_x_axis, int move_on_y_axis);
    private:
        int m_mem_size;
        static const int N_MEMBERS = 20;
        
        Shape *m_list[N_MEMBERS];
    };

    /**************************************************************************/

}

#endif /* __SHAPES_HPP__ */

