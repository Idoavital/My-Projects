#include <iostream>

template <typename T>
T Max (T t1, T t2)
{
    return t1>t2 ? t1 : t2;
}
int main(int argc, char *argv[])
{
   /* int arr[12];
    std::cout<<Max<int>(3,5)<<" "<<Max<double>(3.7,12.3)<<" "<<std::endl;
    std::cout<<Max<int*>(arr,arr+8)<<std::endl;
    std::cout<<Max('a','b')<<std::endl;*/

    return 0;
}
