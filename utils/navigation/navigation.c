#include <assert.h> /* assert */
#include <stdlib.h> /* malloc*/
#include <stdio.h> /* printf  for test*/

#include "navigation.h"
/*	Opaque path structure	*/
 struct path
 {
 	size_t pathOrder[64];
	size_t distance;
	size_t junc_num;
 };

typedef struct junc_info
{
   size_t junc;
   size_t distance;

}JUNC_INFO;

static void setDistance ( size_t dest , size_t src , size_t distance);

/*recursion function*/
static int navigationHelper (PATH_T *global_path, PATH_T local_path, int src , int dest ,size_t visit_junc, int index);
/*check if the bit index in the "visit_junck" bit array is on*/
static int checkIfVisit (size_t visit_junc, int index);
/* set on the bit index */
static size_t setVisit (size_t visit_junc, int index);



JUNC_INFO (*junc_map)[4];

/****************************************************************************************/
/*	initialize solution structures  */
int SPinitialize(size_t (* adj)[4], size_t adj_size, DIST dist[], size_t dist_size)
{
    int i = 0, j = 0;

    /*allocate memory to the junction list*/
    junc_map = calloc((adj_size+1) , sizeof(junc_map[0]));

    if (NULL == junc_map)
    {
        return -1;
    }


    /* initialize the junc number*/
    for (i = 1; i <= adj_size; i++)
    {
        for(j =0; j < 4; j++)
        {
            junc_map[i][j].junc = adj[i][j];
        }
    }

        /*set distance */
    for (i = 0; i < dist_size; i++)
    {
        setDistance (dist[i].dest ,dist[i].src ,dist[i].dist );
        setDistance (dist[i].src ,dist[i].dest ,dist[i].dist ); /*set the off*/
    }

    atexit(SPdestroy);
    return 0;
}


static void setDistance ( size_t dest , size_t src , size_t distance)
{
    int i =0;
    for (i = 0 ; i< 4  ; i++)
    {
        if (junc_map[dest][i].junc == src)
        {
             junc_map[dest][i].distance = distance ;
        }
    }
}


/*	create shortest path solution  */
PATH_T *SPnavigate(size_t src, size_t dest )
{
    size_t visit_junc = 0;
    PATH_T *global_path = NULL; /* */
    PATH_T local_path = {{0},0,0}; /* the struct pass by value to the recorsion */

    global_path = calloc(1, sizeof(*global_path));

        /* check allocate */
    if (global_path == NULL )
    {
        return NULL;
    }

    navigationHelper (global_path, local_path,  src ,  dest , visit_junc , 0);

    return global_path;
}


static int navigationHelper (PATH_T *global_path, PATH_T local_path, int src , int dest ,size_t visit_junc, int index)
{
    int i =0 ;


    /* if the way is longer then the distance return */
    if (global_path->distance < local_path.distance && global_path->distance != 0)
    {
        return 0;
    }

    visit_junc = setVisit ( visit_junc, src);
    local_path.pathOrder[index] = src;
    local_path.junc_num++;

    /* if we get to the end of way */
    /* copy the loacl path to global path*/
    if (src == dest)
    {
        local_path.pathOrder[index] = src;
        *global_path = local_path;
        return 0;
    }
    for (i=0; i < 4; i++)
    {
        /*if continue  the next junction is unvisited */
             /* update the local struct */
        if (0 !=junc_map[src][i].junc
                    && 0 == checkIfVisit ( visit_junc,  junc_map[src][i].junc))
        {

            {
                 local_path.distance += junc_map[src][i].distance;
                 navigationHelper (global_path, local_path, junc_map[src][i].junc ,  dest , visit_junc,  index+1);
                 local_path.distance -= junc_map[src][i].distance;
            }
        }
    }

    return 0;
}


static int checkIfVisit (size_t visit_junc, int index)
{

    return (visit_junc &=  1L << index ) ;
}

/* set on the bit index */
static size_t setVisit (size_t visit_junc, int index)
{

    return (visit_junc |=  1L << index ) ;
}
/*	Disposes of the resources used by 'path'                */
void SPdestroyPath(PATH_T *path)
{
    free(path);
}
/*	Disposes of the resources used by solution structure    */
void SPdestroy(void)
{
    free(junc_map);
}

/*	print the solution path */
void SPprintPath(PATH_T *path, DETAIL detail_level)
{

    int i = 0;
    assert(NULL != path );
    for (i = 0  ; i < path->junc_num ; i++)
        printf(" %lu ",path->pathOrder[i]);
    printf("\n junc number %lu ",path->junc_num);
    printf("\n junc distance %lu ",path->distance);
}

/* func to check if initiallize completed */

int getDistance(int src , int dest)

{
    int j = 0;

    for(j = 0 ; j < 4 ;j ++)
    {
        if(junc_map[src][j].junc == dest)
        {
            return (junc_map[src][j].distance);
        }
    }
    return -1;

}

/*	get the solution path */
size_t *SPgetPath(PATH_T *path, size_t *size)
{
        *size =path->distance;
    return path->pathOrder;
}


