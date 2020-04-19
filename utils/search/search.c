
#include <math.h>/* Square*/

#include "search.h"


static void * binarySearchHelper(char* base, int left , int right, size_t size_elem , CMP_T cmp ,const void * data);

static void * binarySearchIterativeHelper(char* base, int left , int right, size_t size_elem , CMP_T cmp ,const void * data);


/******************************************binarySearch  sort O(log-n) ***************************************************/

void * binarySearch(void* base, size_t num_elem, size_t size_elem , CMP_T cmp ,const void * data)
{

   return  binarySearchHelper(base, 0 , num_elem-1,   size_elem , cmp , data);

}

void * binarySearchIterative(void* base, size_t num_elem, size_t size_elem , CMP_T cmp ,const void * data)
{

   return  binarySearchIterativeHelper(base, 0 , num_elem,   size_elem , cmp , data);

}
/******************************************jumpSearch  sort O(log-n) ***************************************************/
void * jumpSearch(void* base, size_t num_elem, size_t size_elem , CMP_T cmp ,const void * data)
{
    int jump = 0;
    int i =0 , j = 0;
    jump =  sqrt(num_elem);


    for ( i = jump ; i<(num_elem-1+jump)  ; i+= jump)
    {
        /*for the last block : if the jump is bigger then the last elemnet*/
        i = i < (num_elem-1) ? i :num_elem-1 ;
        /* find the block of data */
        if (cmp( data ,((char*)base + i*size_elem) ) <= 0)
        {
            /*find the data in the block*/
            for ( j = i-jump ; j <= i ; j++)
            {
                if (cmp( data ,(char*)base + j*size_elem) ==0 )
                {
                    return ((char*)base + j*size_elem);
                }

            }
            return NULL;
        }
    }

    return NULL;


}
/*******************************************static functoins *********************************************************/
static void * binarySearchHelper(char* base, int left , int right, size_t size_elem , CMP_T cmp ,const void * data)
{
    int mid =0;

    mid = ( left + right) / 2 ;

    if (left <= right)
    {

        if ( cmp(data , base+ mid * size_elem)== 0)
        {
            return (base + mid * size_elem);
        }

        if (cmp(data , base+ mid * size_elem)< 0)
        {
            return binarySearchHelper(base, left , mid-1, size_elem , cmp , data);
        }
        else
        {
            return binarySearchHelper(base,  mid+1 , right , size_elem , cmp , data);
        }
    }

    return  NULL;
}


static void * binarySearchIterativeHelper(char* base, int left , int right, size_t size_elem , CMP_T cmp ,const void * data)
{
    int mid =0;



    while (left <= right)
    {
          mid = ( left + right) / 2 ;

        if ( cmp(data , base+ mid * size_elem)== 0)
        {
            return (base + mid * size_elem);
        }

        if (cmp(data , base+ mid * size_elem)< 0)
        {
            left = mid+1;
        }
        else
        {
            right = mid+1;
        }
    }

    return  NULL;
}

