#include <iostream>

struct X
{
    explicit X();

    explicit X(int a_, int b_ = 8);

    ~X();

    X(const X& other_);

    X& operator = (const  X& other_);

    int m_a;

    int m_b;

};

struct Y
 {
     X m_x;
     int m_i;
 };

X::X(): m_a (3) , m_b (4)
{
    std::cout <<"this:"<< this << " x defulat ctor m_a " << m_a
                << " m_b " << m_b << std::endl;
}

X::X (int a_ ,int b_ ): m_a(a_) , m_b(b_)
{
    std::cout <<"this:"<< this << " x int int ctor m_a " << m_a
            << " m_b " << m_b << std::endl;
}

X::X (const X& other_): m_a (other_.m_a),m_b (other_.m_b)
{
    std::cout <<"this:"<< this << " x copy ctor m_a " << m_a
            << " m_b " << m_b << std::endl;
}

X&X::operator =  (const X& other_)

{
     std::cout <<"this:"<< this << " x assignment operator m_a " << m_a
            << " m_b " << m_b << std::endl;
    return *this;
}

X::~X()
{
    std::cout <<"this:"<< this << " x Dtor. m_a " << m_a
            << " m_b " << m_b << std::endl;
}



int main (int argc , char * argv[])
{
    X x1;
    X x2(7);
    X* px = new X (x2);
    X x3 (9,10);
    X X4 (x1);
    X *xp = new X[10];

    x1 = x3 ;
    delete[] xp;
    delete px; px =0;

    Y y1;
    y1.m_x.m_a = 250;
    y1.m_x.m_b =750;

    Y y2(y1);
    Y y3;

    y3 =y1;

    return 0;
}
