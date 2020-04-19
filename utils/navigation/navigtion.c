#include <assert.h> /* assert */
#include <stdlib.h> /* malloc*/

#include "navigation.h"
/*	Opaque path structure	*/
 struct path
 {
 	size_t pathOrder[64];
	size_t distance;
 };

typedef struct junc_info
{
   int junc;
   int distance;

}JUNC_INFO;

static void setDistance ( int dest , int src , int distance);

JUNC_INFO (*junc_map)[4];

/*	initialize solution structures  */
int SPinitialize(int (* adj)[4], size_t adj_size, DIST dist[], size_t dist_size)
{
    int i = 0, j = 0;

    /*allocate memory to the junction list*/
    junc_map = malloc((adj_size+1) * sizeof(junc_map[0]));

    /* initialize the junc number*/
    for (i = 1; i <= adj_size; i++)
    {
        for(j =0; j < 4; j++)
        {
            junc_map[i][j].junc = adj[i][j];
        }
    }

        /*set distance */
    for (i = 0; i <= dist_size; i ++)
    {
        setDistance (dist[i].dest ,dist[i].src ,dist[i].dist );
        setDistance (dist[i].src ,dist[i].dest ,dist[i].dist );
    }

    return 0;
}


static void setDistance ( int dest , int src , int distance)
{
    int i =0;
    for (i = 0 ; i< 4  ; i++)
    {
        if (junc_map[dest][i].junc == src )
        {
            junc_map[dest][i].distance = distance;
        }
    }
}


/*	create shortest path solution  */
PATH_T *SPnavigate(int src, int dest[], size_t dest_size)
{

}

