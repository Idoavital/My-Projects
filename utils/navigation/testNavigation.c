
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "navigation.h"

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

int main(int argc, char *argv[])

{

     PATH_T * path_1 = NULL;
     PATH_T * path_2 = NULL;
      DIST dist[] =
      {
          #include "distance.dat"
      };
      size_t adj[][4] =
      {
          #include "adjacency.dat"
      };

      SPinitialize(adj, ARRAY_SIZE(adj), dist, ARRAY_SIZE(dist));

       if(130 == getDistance(1 , 2))
        {
            printf("SPinitialize succeeded\n");
        }
        else
        {
            printf("SPinitialize failed\n");
        }
        if(130 != getDistance(2 , 1))
        {

            printf("SPinitialize failed\n");

        }
        printf("\n----way  from %d to %d----\n ",atoi(argv[1]) ,atoi(argv[2]) );
        path_2 = SPnavigate( atoi(argv[1]), atoi(argv[2]) );
        SPprintPath(path_2 , 0);

        printf("\n----way  from 29 to 5---- \n");
        path_1 = SPnavigate( 10, 1 );
        SPprintPath(path_1 , 0);

        SPdestroyPath(path_1);
        SPdestroyPath(path_2);

        return 0;
}


