#include <stdlib.h> /* malloc */
#include <assert.h> /* assert*/

#include "sortL.h" 
#include "DList.h"


struct SortL
{
	DL_T *dl;
	IsBefore_t myCmp;
};
/* Creates a sorted list. Returns NULL on failure. */
SORT_L *SortCreate(IsBefore_t compFunc)
{
	SORT_L *sl =(SORT_L *) malloc (sizeof(SORT_L));
	
	if (sl== NULL)
	{
		return NULL;
	}
	
	sl->dl = DLCreate();
	if (sl->dl == NULL)
	{
		free (sl);
		return NULL;
	}
	
	sl->myCmp = compFunc;
	
	return sl;
}

/* Disposes of resources used by sl.                                           */
void SortDestroy(SORT_L *sl)
{
	assert (NULL != sl);
	
	DLDestroy(sl->dl);
	free (sl);
}

/* Inserts a new element (containing 'data') in 'sl'. Returns an iterator
   pointing at this new element. Returns SortEnd on failure.                   */
SORT_ITER_T SortInsert(SORT_L *sl, void *data)
{

	SORT_ITER_T sort_it  = {NULL};
	assert (NULL != sl);
	
	for (sort_it.dl_it = DLBegin(sl->dl) ;
					 1 != DLIsEqual (sort_it.dl_it ,DLEnd(sl->dl) ) ;
									 sort_it.dl_it = DLNext (sort_it.dl_it))
	{
		if (1 == sl->myCmp (DLGetData( sort_it.dl_it),data))
		{
			break ;
		}
	}
	sort_it.dl_it = DLInsert(sl->dl, sort_it.dl_it, data);
	
	return sort_it;
}

/*******************************************************************************/
/* Erases the element pointed to by iterator 'it' from list 'sl'.              */
SORT_ITER_T SortErase(SORT_L *sl, SORT_ITER_T it)
{
	
	SORT_ITER_T sort_it  = {NULL};
	assert (NULL != sl);
	
	sort_it.dl_it = DLErase(sl->dl, it.dl_it);
	
	
	return sort_it;
}


/*******************************************************************************/
/* Remove item from end of list                                                */
void SortPopBack(SORT_L *sl)
{
	assert (NULL != sl);
	 PopBack(sl->dl);
}

/*******************************************************************************/
/* Remove item from end of list                                                */
void SortPopFront(SORT_L *sl)
{
	assert (NULL != sl);
	 PopFront(sl->dl);
}
/*******************************************************************************/
/* Returns the number of items in the list.                                    */
size_t SortSize(const SORT_L *sl)
{
	assert (NULL != sl);

	return DLSize(sl->dl);
	
}
/*******************************************************************************/
/* Returns 1 if list is empty. Returns 0 otherwise.                            */
int SortIsEmpty(const SORT_L *sl)
{
	assert (NULL != sl);
	return DLIsEmpty(sl->dl);
}	
/*******************************************************************************/
/* Returns data pointed to by iterator 'it'.                                   */
void *SortGetData(SORT_ITER_T it)
{
	return (DLGetData(it.dl_it));
}
/*******************************************************************************/
/* Returns an iterator pointing to the begining of the list.                   */
SORT_ITER_T SortBegin(const SORT_L *sl)
{
	SORT_ITER_T it;
	assert (NULL != sl);
	
	it.dl_it = DLBegin(sl->dl);
	return it;
}
/*******************************************************************************/
/* Returns an iterator pointing to the end of the list.                        */
SORT_ITER_T SortEnd(const SORT_L *sl)
{
	SORT_ITER_T it;
	assert (NULL != sl);
	it.dl_it = DLEnd(sl->dl);
	return it;
}

/*******************************************************************************/
/* Traverses the iterator to the next item in the list.                        */
SORT_ITER_T SortNext(SORT_ITER_T it)
{
	it.dl_it = DLNext(it.dl_it);
	return it;
}
/*******************************************************************************/
/* Traverses the iterator to the previous item in the list.                    */
SORT_ITER_T SortPrev(SORT_ITER_T it)
{
	it.dl_it = DLPrev(it.dl_it);
	
	return it;
}

/*******************************************************************************/
/* Returns 1 if iterators 'it1' and 'it2' are the same. Returns 0 otherwise.   */
int SortIsEqual(SORT_ITER_T it, SORT_ITER_T it2)
{
	return (DLIsEqual(it.dl_it, it2.dl_it));
}

/*******************************************************************************/
/* Returns iterator pointing at first element with 'data' from iterator it.
   Returns SortEnd if 'data' was not found.                                    */
SORT_ITER_T SortFind(const SORT_L *sl, SORT_ITER_T it, IsMatch_t matchFunc, const void *data, void *param)
{
	
		while  ( 1 != SortIsEqual (it, SortEnd( sl)))
		{
			if (1 == matchFunc (SortGetData (it), data, param))
			{
				return it;
			}
			
			it = SortNext(it);
		}
			
	return it;
}
/*******************************************************************************/
/* Merges list 'src' into list 'dst'                                           */
SORT_ITER_T SortMerge(SORT_L *dst, SORT_L *src)
{
	
	SORT_ITER_T it_dst = SortBegin(dst);
	SORT_ITER_T it_begin =  SortBegin(src) ;
	SORT_ITER_T it_end  = SortEnd(src);

	
	it_end  =  it_begin;
	
	/* run from the begin of dst until the end*/
	for (it_dst = SortBegin(dst) ; 
				1 != SortIsEmpty (src ) && 1 != SortIsEqual (it_dst, SortEnd( dst))
							 ; it_dst = SortNext (it_dst))
	
	{
	 	/*  find if the data  of it_begin is bigger then the data of it_dst */
		if (1 == dst->myCmp(SortGetData( it_dst ),SortGetData (it_begin)))
		{
			/*	run until the first element  in the src list is bigger then it_dst */
			/*	to find sort sub list that could place in the befor it_dst  */ 
			for (it_end  =  it_begin; 
			  1 !=SortIsEqual (it_end , SortEnd (src)) &&
				 1 != dst->myCmp (SortGetData( it_end), SortGetData( it_dst)) 
										 ; it_end = SortNext( it_end));
										 
										 
			/* splice the sub list from src to dst and update the iterators for the next loop*/
		it_end = SortPrev( it_end);
		DLSplice(it_dst.dl_it, it_begin.dl_it , it_end.dl_it);
		it_dst.dl_it.adj = it_end.dl_it.curr;
		it_begin = SortBegin(src) ;			
		}	
	
	}
	
	   /*in a case there is a members in the src list is bigger from rhe dst src */
	if (SortIsEqual(it_dst, SortEnd( dst)) == 1 && 1 != SortIsEmpty(src))
	{
		it_end  = SortEnd(src);
		it_end = SortPrev( it_end);
		DLSplice(SortEnd(dst).dl_it, SortBegin(src).dl_it ,it_end.dl_it);
	}
	
	return SortBegin(dst); 
}











