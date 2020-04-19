#ifndef __NAV_H__
#define __NAV_H__

#include <stddef.h>		/*	size_t	*/


/*  print type  */
typedef enum {JUNCTIONS} DETAIL;   /*   print specification */

/*	Opaque path structure	*/
typedef struct path PATH_T;

/*  distance data struct    */
typedef struct
{
    size_t src;
    size_t dest;
    size_t dist;
} DIST;

/*	initialize solution structures  */
int SPinitialize(size_t (* adj)[4], size_t adj_size, DIST dist[], size_t dist_size);

/*	create shortest path solution  */
PATH_T *SPnavigate(size_t src, size_t dest );

/*	print the solution path */
void SPprintPath(PATH_T *path, DETAIL detail_level);

/*	get the solution path */
size_t *SPgetPath(PATH_T *path, size_t *size);

/*	Disposes of the resources used by 'path'                */
void SPdestroyPath(PATH_T *path);

/*	Disposes of the resources used by solution structure    */
void SPdestroy(void);



/*******************or test **********************/
/* func to check if initiallize completed */

int getDistance(int src , int dest);


#endif /* __NAV_H__ */
