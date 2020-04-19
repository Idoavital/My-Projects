#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#include "DList.h"
#include "DLIter.h"

 struct Node_dl_t
{
	void* data;
	void* link; /* xor of after and adj addresses */
};

struct DList 
{
	DL_NODE_T *back;
	DL_NODE_T *front;
		
} ;



DL_NODE_T *Xor(DL_NODE_T * first ,DL_NODE_T * second );


/*************************************************************************************/
/* create a new node */
/* the user must free the memory */
DL_NODE_T* nodeCreate()
{
	DL_NODE_T* node = (DL_NODE_T*)calloc(1,sizeof(DL_NODE_T));
	if (NULL == node)
	{
		return NULL;
	}
	
	return node;
}

/*************************************************************************************/
/* Creates a doubly linked list. Returns NULL on failure. */
/* the user must free the memory */

DL_T* DLCreate(void)
{
	DL_T *dlist = (DL_T*)malloc (sizeof(DL_T));
	/* check if allocate success */
	if (NULL == dlist)
	{
		return NULL;
	}
	
	/* create two dummy node */
	dlist->back = nodeCreate();
	dlist->front = nodeCreate();
	
	/* check if allocate success */
	if(dlist->front == NULL || dlist->back == NULL)
	{
		free(dlist);
		return NULL;
	}
	
	dlist->front->link = dlist->back;
	dlist->back->link = dlist->front;
	
	return dlist;
}

/*************************************************************************************/
/* Remove item from end of list*/
void PopBack(DL_T* dl)
{


	DL_NODE_T *temp = dl->back;
	
	assert (NULL != dl);
	
	dl->back = dl->back->link; 
	dl->back->link = Xor(dl->back->link ,temp );
	dl->back->data = NULL;
	free(temp);
}

/*************************************************************************************/
/* Remove item from front of list*/
void PopFront(DL_T* dl)
{
	DL_NODE_T *temp = dl->front;
	assert (NULL != dl);
	
	
	dl->front =  dl->front->link; /* in the front link there is the adress of the adj member*/
	dl->front->link = Xor(dl->front->link ,temp ); /* update the link after pop the front member*/
	dl->front->data = NULL;
	free(temp);
}

/*************************************************************************************/
/* Add item to end of list. Returns an iterator pointing to this item. */
DL_ITER_T PushFront(DL_T* dl, void *data)
{
	DL_ITER_T temp_iter ={ NULL, NULL };
	DL_NODE_T *dummy = nodeCreate();
	/* check if a success to allocate a new memory */
	if (NULL == dummy)
	{
		return temp_iter;
	}
	
	
	assert (NULL != dl);

	temp_iter.adj = dummy; 
	temp_iter.curr = dl->back;
	
	dl->back->data = data;
	dummy->link = dl->back;
	dl->back->link = Xor(dl->back->link, dummy);
	dl->back = dummy;
	
	return temp_iter;
}

/*************************************************************************************/
/* Add item to front of list. Returns an iterator pointing to this item. */
DL_ITER_T PushBack(DL_T* dl, void *data)
{
	DL_ITER_T temp_iter ={ NULL, NULL };
	DL_NODE_T *dummy = nodeCreate();
	/* check if a success to allocate a new memory */
	if (NULL == dummy)
	{
		return temp_iter;
	}
	assert (NULL != dl);
	
	temp_iter.adj = dl->front->link;  /* */
	temp_iter.curr = dl->front;
	
	dl->front->data = data;
	dummy->link = dl->front;
	dl->front->link = Xor(dl->front->link, dummy);
	dl->front = dummy;
	
	return temp_iter;
}
/*************************************************************************************/
/* Returns the number of items in the list. */
size_t DLSize(const DL_T *dl)
{
	DL_ITER_T temp = DLBegin(dl) ; 
	size_t count =0 ;
	while (temp.curr != dl->front)
	{
		temp = DLNext(temp);
		count++;
	}
	return count;
}

/*************************************************************************************/
/* Returns 0 if list is empty. Returns 1 otherwise. */
int DLIsEmpty(const DL_T *dl)
{
	if (dl->front == dl->back->link)
		return 1;
		
	return 0;
}
/*************************************************************************************/
/* Disposes of resources used by DL_T. */
void DLDestroy(DL_T *dl)
{
	while(0 == DLIsEmpty(dl))
	{
		PopFront(dl);
	}
	free(dl->front);
	free(dl->back);
	free(dl);
}
/*************************************************************************************/
/* Returns data pointed to by iterator 'it'.*/
void* DLGetData(DL_ITER_T it)
{
	return it.curr->data;
}
/*************************************************************************************/
/* Advances the iterator to the next item in the list. */
DL_ITER_T DLNext(DL_ITER_T it)
{
	DL_ITER_T ret = {NULL ,NULL};
	ret.curr = Xor(it.curr->link, it.adj);
	ret.adj = it.curr;
	
	return ret;
}
/*******************************************************************************/
/* Traverses the iterator to the previous item in the list. */
DL_ITER_T DLPrev(DL_ITER_T it)
{
	DL_ITER_T ret = {NULL ,NULL};
	ret.curr =it.adj;
	ret.adj =Xor(it.adj->link, it.curr);
	
	return ret;
}
/*************************************************************************************/
/* Returns an iterator pointing to the begining of the list. */
DL_ITER_T DLBegin(const DL_T *dl)
{
	DL_ITER_T temp = {NULL ,NULL};
	temp.curr = dl->back->link;
	temp.adj = dl->back;
	
	return temp;
}
/*************************************************************************************/
/* Returns an iterator pointing to the end of the list. */
DL_ITER_T DLEnd(const DL_T *dl)
{
	DL_ITER_T temp = {NULL ,NULL};
	temp.curr = dl->front;
	temp.adj =  dl->front->link;
	
	return temp;
}
/*************************************************************************************/
/* Returns 1 if iterators 'it' and 'endIt' are the same. Returns 0 otherwise. */
int DLIsEqual(DL_ITER_T it, DL_ITER_T endIt)
{
	
		if (it.curr == endIt.curr)
		{
			return 1;
		}
	return 0;
}
/*******************************************************************************/
/* Erases the element pointed to by iterator 'it' from list 'dl'. */
DL_ITER_T DLErase(DL_T *dl, DL_ITER_T it)
{

	DL_NODE_T *befor_it = it.adj ;
	DL_NODE_T *after_it = Xor (it.curr->link, it.adj) ;
	
		/* update the new link of node befor it  */
	befor_it->link = Xor( it.adj->link , it.curr); 
	befor_it->link = Xor ( befor_it->link ,after_it);
	
		/* update the new link of node befor it  */
	after_it->link = Xor ( it.curr, after_it->link );
	after_it->link = Xor (after_it->link, befor_it );
	
	/* free the old node */
	free(it.curr);
	it.curr = after_it;
	it.adj = befor_it;
	
	 
	return it;
}
/*******************************************************************************/
/* Inserts a new element (containing 'data') in 'dl' before the element pointed
   to by iterator 'it'. Returns an iterator pointing at this new element. Returns
   DLEnd on failure. */
DL_ITER_T DLInsert(DL_T *dl, DL_ITER_T it, void *data)
{
	DL_NODE_T *new_node = nodeCreate();
	DL_NODE_T *befor_it =  it.adj;
	DL_NODE_T *after_it = it.curr ;
	
	new_node->data = data;
	new_node->link = Xor(befor_it, after_it );
	
		/* update the link of nodes */
	befor_it->link = Xor( befor_it->link, it.curr);
	befor_it->link = Xor( befor_it->link, new_node);
	after_it->link = Xor (new_node, Xor(it.curr->link,it.adj)); /*DLNext (it.curr) */
	
	it.adj = befor_it;
	it.curr = new_node;
	return it;
}
/*******************************************************************************/
/* Inserts the items in source list (between srcBegin and srcEnd) before position
   pointed to by dst in destnation list.                                      */

void DLSplice(DL_ITER_T dst, DL_ITER_T srcBegin, DL_ITER_T srcEnd)
{
	DL_NODE_T *befor_begin_n = NULL ;
	DL_NODE_T *after_end_n =  NULL ;
	
	/* first disconnect from the list the nodes between begin to end*/
	/* and connect the node befor begin to the node after end of */
	
	befor_begin_n  = srcBegin.adj ; /* get the node befor begin */
	after_end_n = Xor(srcEnd.curr->link ,srcEnd.adj);	/* get the node after end */
	
		/* update the new link of node befor begin */
	befor_begin_n -> link = Xor(befor_begin_n->link , srcBegin.curr ) ; 
	befor_begin_n -> link =  Xor (befor_begin_n -> link , after_end_n ) ;
	
		/* update the new link of node after end */
	after_end_n->link = Xor(srcEnd.curr , after_end_n-> link );
	after_end_n->link = Xor (after_end_n->link , befor_begin_n );
	
	
	/* connect the node befor begin to the node after end of */
	dst.adj->link = Xor (dst.adj->link, dst.curr );
	dst.adj->link = Xor (dst.adj->link, srcBegin.curr);
	
	dst.curr->link = Xor (dst.curr->link, dst.adj);
	dst.curr->link = Xor (dst.curr->link, srcEnd.curr);
	/*	connect the new range nodes to srcEnd */
	
	srcBegin.curr->link = Xor (srcBegin.curr->link,srcBegin.adj );
	srcBegin.curr->link = Xor (srcBegin.curr->link, dst.adj);
	
	srcEnd.curr->link = Xor (srcEnd.curr->link, after_end_n);
	srcEnd.curr->link = Xor (srcEnd.curr->link, dst.curr);
}

/*************************************************************************************/
DL_NODE_T *Xor(DL_NODE_T * first ,DL_NODE_T * second )
{
	size_t a = (size_t) first;
	size_t b = (size_t) second;
	size_t c = a^b;
	
	
	return ((DL_NODE_T *)c);
}
















