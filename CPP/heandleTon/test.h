


#ifndef TEST_H
#define TEST_H

#include <stdlib.h>

namespace ilrd
{

    class test
    {

    public:

      int print(void)
      {
       return m_x;
      }

      int add(int num)
      {
          m_x+=num;
        return (m_x);
      }
    private:
      int m_x;
      friend class singleTon<test>;
      test(int x = 0):m_x(x){};
    };
}
#endif /*TEST_H */
