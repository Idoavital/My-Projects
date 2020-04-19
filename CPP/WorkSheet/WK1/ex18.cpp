#include <iostream>


int main(int argc, char *argv[])
{
    int i=8;
    int &ip = i;
    ip =9 ;

    std::cout << i  << sizeof(ip)<<  " size of i"<< sizeof(i)<< std::endl;

    return 0;
}
