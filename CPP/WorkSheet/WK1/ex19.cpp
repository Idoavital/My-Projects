#include <iostream>


void Foo (const double& i)
{
     std::cout << " const \n"<< &i <<std::endl;
}
void bao(double& i)
{
         std::cout << " double \n"<< &i <<std::endl;
         i =97987.76986;
}

int main(int argc, char *argv[])
{
    int i =5;
    int y = 0;
 std::cout << " int main \n"<< &i <<std::endl;
    Foo(i);


    bar(reinterpret_cast<double&>(i));
/*
    std::cout << " \n" << i << std::endl;
    std::cout << " \n" << y << std::endl;*/

    return 0;
}
