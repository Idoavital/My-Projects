#include <stdlib.h> /* malloc*/
#include <assert.h> /*assert */

#include "BST.h"


typedef enum
{
    LEFT ,
    RIGHT
}CHILDREN;

typedef struct bst_node
{
	void* data;
    struct bst_node* parent;
    struct  bst_node* child[2];
}BST_NODE;

struct bst_t
{
    BST_NODE* dummy;
    COMP_T cmp;
    void* param;
};

/**/
static BST_NODE* nodeCeate ();

/* return the min of the node*/
static BST_NODE* minNode(BST_NODE* node);

/* return the max of node*/
static BST_NODE* maxNode(BST_NODE* node);

/*remove node with one child */
static void removeNode(BST_NODE* curr , int left_or_right);

/*remove node with no child */
static void removeNodeNoChilde(BST_NODE* node);

/* if one or two child null*/
static void *removeOneOrTwo(BST_NODE* curr );


/* Creates a Binary Sorted Tree */
BST_T *BSTCreate(COMP_T cmp, void *param)
{
	BST_T * root =NULL;
	root = calloc (1,sizeof(BST_T));
	if (NULL== root )
	{
		return NULL;
	}
	
	root->dummy = nodeCeate(NULL);
	if (NULL == root->dummy)
	{
		free(root);
		return NULL;  
	}
	root->cmp = cmp;
	root->param = param;
	
	return root;
}


/* Inserts 'data' into the BST. Returns an iterator representing the element.
   Returns BSTEnd() if unsuccessful */
BST_ITER BSTInsert(BST_T *bst,  void *data)
{

	BST_NODE* new_n = NULL;
	BST_NODE* temp_parent = NULL;
	BST_NODE* next= NULL;
	int cmp_ret = -1;
	
	assert (NULL!= bst);
	
	next = bst->dummy->child[LEFT]; /* the root of the tree */

	new_n = nodeCeate(data);
	
	
	
	temp_parent = bst->dummy;
	/* find a perant for the new node */
	while (next != NULL)
	{
		cmp_ret = bst->cmp(data , next->data  , bst->param) ;
		temp_parent = next;
		
		if(cmp_ret == 0)
		{
			free(new_n);
			return next;
		}
		next =next->child[cmp_ret > 0] ;
	}
		
	new_n->parent = temp_parent;
		
	/* if the now node bigger then the current node -> insert the new node in the right child*/
	/* else insert to the left child */
	temp_parent->child[cmp_ret>0] = new_n;
	
	return new_n;	
}

/* Returns the number of items in the BST (in O(n) time)*/
size_t BSTCount(const BST_T *bst)
{
	BST_ITER temp =  BSTBegin(bst);
	BST_ITER end = BSTEnd(bst);
	size_t count = 0;
	for ( ; 1 != BSTIsSameIter( temp , end) ; temp = BSTNext(temp) , count++ )
	{}
	
	return count;
}

/* Returns the data in the element pointed to by iterator 'it' */ 
void *BSTGetData(BST_ITER it)
{
	return ((BST_NODE*)it)->data;
}

/* Returns 1 if 'bst' is empty, 0 otherwise (in O(1) time)*/
int IsEmpty(const BST_T *bst)
{	
	return bst->dummy->child[LEFT]==NULL ? 1 : 0;
}



/* Returns an iterator pointing to the first element in 'bst' */
BST_ITER BSTBegin(const BST_T *bst)
{
	assert (NULL != bst);

	return (minNode(bst->dummy));
}

/* Returns an iterator representing the end of 'bst' */
BST_ITER BSTEnd(const BST_T *bst)
{
	return bst->dummy;
}

/* Traverses the iterator to the next element in the BST. */
BST_ITER BSTNext(BST_ITER it)
{
	BST_NODE* next= (BST_NODE*) it;

	
	/* if there is a right child so the minimum of the right child is the next*/
	if(next->child[RIGHT] != NULL)
	{
		return (BST_ITER) minNode( next->child[RIGHT] ) ;
	}
	
	while (next != next->parent->child[LEFT])
	{
		/*if the iterator is a left child*/
		next = next->parent;
	}
	
	return (BST_ITER)next->parent;
}

/* Traverses the iterator to the previous element in the BST. */
BST_ITER BSTPrev(BST_ITER it)
{
	BST_NODE* next= (BST_NODE*) it;

	assert (it != NULL);
	
	/* if there is a left child so the maximum of the left child is the prev*/
	if(next->child[LEFT] != NULL)
	{
		return (BST_ITER) maxNode( next->child[LEFT] ) ;
	}
	
	/* find the first node that he is a fight child */
	while (next->parent != NULL )
	{
		/*if the iterator is a left child*/
		if (next == next->parent->child[RIGHT])
		{
			return (BST_ITER)next->parent;
		}
		next = next->parent;
	}
	return (BST_ITER)next;
	
}


/* Returns 1 if 'it1' is the same as 'it2'. Returns 0 otherwise. */
int BSTIsSameIter(BST_ITER it1, BST_ITER it2)
{
	if (it1 == it2)
		return 1;
		
	return 0;
}


/* Returns 1 if 'it' is an invalid iterator. Returns 0 otherwise. */
int BSTIsBadIter(BST_ITER it)
{
	if (it == NULL)
		return 1;
		
	return 0;
}

/* Returns iterator pointing at first element, which matches 'data'.
   If the element is not found, returns BSTEnd(). */
BST_ITER BSTFind(const BST_T *bst, const void *data)
{
	int cmp_ret = 0;
	BST_NODE* next =  bst->dummy->child[LEFT];
	
	while (next != NULL)
	{
		cmp_ret = bst->cmp(data , next->data  , bst->param) ;	
		if(cmp_ret == 0)
		{
			return next;
		}
		next =next->child[cmp_ret > 0] ;
	}

	return next;
}

/* Executes function 'action' on each element in 'bst' (as long as 'action' returns success).
   Returns 0 for success, non-zero otherwise. 'param' is an optional parameter passed into 'action'. */
int BSTForEach(BST_ITER from, BST_ITER to, ACTION_T action, void *param)
{
	BST_ITER temp =  from;
	BST_ITER end = to;
	
	
	for ( ; 1 != BSTIsSameIter( temp , end)  ; temp = BSTNext(temp) )
	{
		if(action (((BST_NODE*)temp)->data, param))
			return 1;
	}
	
	return 0 ;
}

/* Removes element pointed to by iterator 'it' from the BST. 
   Returns the data in the element. */
void *BSTRemove(BST_ITER it)
{
	BST_NODE* curr = NULL;
	void* data = NULL;
	BST_ITER next = NULL;
	
	assert (NULL != it);
	
	curr = (BST_NODE*)it;
	data = curr->data;
	/* in a case of two child is null */

	 if (NULL == curr->child[LEFT] || NULL == curr->child[RIGHT] )
	{
		data = removeOneOrTwo( curr );
	}
	/* in case there is two child to the node that will removed*/
	else
	{
		next = BSTNext(it);
		curr->data = ((BST_NODE*)next)->data;
		removeOneOrTwo( (BST_NODE*) next);	
	}
	
	
	return data;
}

/* Disposes of the resources used by a Binary Search Tree */
void BSTDestroy(BST_T *bst)
{
	BST_NODE* temp =  NULL;
	BST_NODE* parent_t = NULL;
	int size = 0 ;
	temp =bst ->dummy->child[LEFT];
	
	if ( !IsEmpty(bst))
	{
	
		while (NULL != temp->parent)
		{
	
			if(temp->child[LEFT] == NULL && temp->child[RIGHT] == NULL )
			{
				parent_t = temp->parent;
				removeNodeNoChilde(temp);
				temp = parent_t; 
			}
			else
			{
				size =  temp->child[LEFT] != NULL ? 0   : 1 ;
				temp= temp->child[size];
			}
		}
	}
	free(bst ->dummy);
	free(bst);
	return;
}


/******************** static functoin ***********************************/
static void *removeOneOrTwo(BST_NODE* curr )
{
	void* data = NULL;
	data = curr->data;
	/* in a case of two child is null */
	if ( (NULL == curr->child[LEFT]) && (NULL == curr->child[RIGHT] ) )
	{
		removeNodeNoChilde( curr);
	}
	
	/* in a case of one child is null */
	else 
	{
		if (NULL == curr->child[RIGHT])
		{
			removeNode(curr , LEFT);
		}
		else
		{
			removeNode(curr , RIGHT);
		}
		
	}
	
	return data;	
}

static void removeNode(BST_NODE* curr , int left_or_right)
{
	BST_NODE* parent = NULL;
	BST_NODE* child_t = NULL;
	
	child_t = curr->child[left_or_right];
	parent = curr->parent;
	
	if(curr == parent->child[LEFT])
	{
		parent->child[LEFT] = child_t;
		child_t->parent = parent;
	}
	else
	{
		parent->child[RIGHT] = child_t;
		child_t->parent = parent;
	}
	free(curr);
	curr=NULL;
}
static void removeNodeNoChilde(BST_NODE* curr)
{
	BST_NODE* parent = NULL;
	parent = curr->parent;
		
	if(curr == parent->child[LEFT])
		parent->child[LEFT] = NULL;
	else
		parent->child[RIGHT] = NULL;
	
	free(curr);
	curr=NULL;		
}
static BST_NODE* minNode(BST_NODE* node)
{	
	assert (NULL != node );
	while (node->child[LEFT] != NULL)
	{
		 node = node->child[LEFT];
	}
	return node;
}

static BST_NODE* maxNode(BST_NODE* node)
{	
	while (node->child[RIGHT] != NULL)
		 node = node->child[RIGHT];
	return node;
}
static BST_NODE* nodeCeate (void *data)
{
	BST_NODE* node =NULL;
	node = calloc (1,sizeof(BST_NODE));
	if (node == NULL)
	{
		return NULL ;
	}
	
	node->data = data ;
	return node;
}





















