
#include <stdio.h>

#include "navigation.h"

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

int main(int argc, char *argv[])
{
DIST dist[] =
  {
      #include "distance.dat"
  };
  int adj[][4] =
  {
      #include "adjacency.dat"
  };

  SPinitialize(adj, ARRAY_SIZE(adj), dist, ARRAY_SIZE(dist));
    return 0;
}


