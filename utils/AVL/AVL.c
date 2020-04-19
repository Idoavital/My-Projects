#include <stdlib.h> /* malloc */
#include <assert.h> /*assert */
#include <stdio.h> /* test printf */

#include "AVL.h"

typedef enum
{
    LEFT ,
    RIGHT
}CHILDREN;

typedef struct node
{

    void *data;
    int high;
    struct node * child[2];
}   NODE;

 struct avl
{
    NODE *root;
    COMP_T  comp;
};
/*************************static helpers function ********************************************/
/* recurSion function to find if a data is in the tree, return pointer to node and null if not found*/
static void* findNode (AVL_T *avl ,NODE* node ,const void * data);
/* find the node and remove the node*/
static int findNodeAndRm (AVL_T *avl ,NODE** node ,const void * data);
/*remove node with only one child */
static void removeNodeOneChild (NODE** node, int diriction);
 /* crate the node wuth the data that the user insert */
static NODE* createNode (void * data);
/* node insert helper function - recursion */
static int nodeInsert(AVL_T *avl, NODE* new_node ,NODE** curr_node);
/* for free nodes */
static void destroyNode(NODE* node);
/* get the height of node , null node return -1 */
static int getNodeHigh(NODE* node);
/* return the max number between num_1 to num_ 2 */
static int max_high (NODE* node_1 ,  NODE* node_2);
/*  helper functoin recursion for "forEach"  */
static int AVLForEachHelper (NODE * node , ACTION_T action, void *param );
/*  helper functoin recursion for "AVLsize"  */
static size_t countNode (NODE * node );
/* get the minimun node*/
static NODE* minNode (NODE * node);
/*********************print tree  **********************************************/
/* Function to line by line print level order traversal a tree*/
static void printLevelOrder( NODE* root);

/* Print nodes at a given level */
static void printGivenLevel(NODE* root, int level);
 /* print node with high */
static void printNode(NODE* node);

/*********************rotate functions****************************************/

static NODE * RR(NODE *node);

static NODE * RL(NODE *node);

static NODE * LL(NODE *node);

static NODE * LR(NODE *node);

/* return the balance of the node */
static int getBalance (NODE *node);

static void swapData (NODE* node_1, NODE* node_2);
 /* check if the balance of the node and rotate if need */
static void chekRotate (AVL_T *avl ,NODE * root );

static NODE* rotate (NODE * root, int direction );
/**********************************************************************************/
AVL_T *AVLCreate(COMP_T cmp)
{
    AVL_T * avl_tree;
    avl_tree = (AVL_T *)malloc (sizeof(AVL_T));

    if (NULL == avl_tree)
    {
        return NULL;
    }

    avl_tree->comp = cmp;
    avl_tree->root = NULL;

    return avl_tree;
}

/* Inserts 'data' into the AVL. Returns 0 if successful.
   Returns non-zero otherwise. */
int AVLInsert(AVL_T *avl, const void *data)
{
    int ret = 0;
    NODE* new_node = createNode((void*)data);
    assert(NULL != avl);

    ret = nodeInsert(avl, new_node , &(avl->root));
    return ret;
}


/* Removes 'data' from 'avl'. Returns 0 if 'data' was found in 'avl'.
   Returns non-zero otherwise. */
int AVLRemove(AVL_T *avl, const void *data)
{
    int ret = 0;

    assert(NULL != avl);

    ret  =findNodeAndRm (avl , &avl->root ,data);

    return ret ;

}
/* Returns the height of 'avl' */
size_t AVLHeight(const AVL_T *avl)
{
    assert(NULL != avl->root);

    return avl->root->high;

}

/* Returns the number of items in the AVL (in O(n) time)*/
size_t AVLSize(const AVL_T *avl)
{
    size_t count = 0;
    assert(NULL != avl->root);
    count = countNode(avl->root);
    return count;
}
/* Disposes of the resources used by 'avl' */
void AVLDestroy(AVL_T *avl)
{
    destroyNode(avl->root);
    free (avl);
}

/* Executes function 'action' on each element in 'AVL' (as long as 'action' returns success).
   Returns 0 for success, non-zero otherwise. 'param' is an optional parameter passed into 'action'.
   Traverses the tree IN ORDER. */
int AVLForEach(AVL_T * avl ,  ACTION_T action, void *param)
{
     int ret = 0;
     ret = AVLForEachHelper (avl->root , action, param );

     return ret;
}
/* Returns 1 if 'AVL' is empty, 0 otherwise (in O(1) time)*/
int IsEmpty(const AVL_T *avl)
{

        if (NULL == avl->root)
            return 1;
    return 0;
}

void *AVLFind( AVL_T *avl, const void *data)
{
   return findNode (avl , avl->root,  data);
}
/*************************static functions ***********************************************/

/* crate the node with the data that the user insert */
static NODE* createNode (void * data)
{
    NODE *node = (NODE*) malloc(sizeof(NODE));
    if (NULL == node)
    {
        return NULL;
    }
    node->data = data;
    node->child[LEFT] = NULL;
    node->child[RIGHT] = NULL;
    node->high = 0;

    return node;
}

static void* findNode (AVL_T *avl ,NODE* node ,const void * data)
{
    int cmp = 0;

     if (node == NULL)
     {
        return NULL;
     }

    cmp = avl->comp(node->data, data);
    if (0 == cmp)
    {
        return node->data;
    }

    return findNode(avl,node->child[cmp < 0], data);

}

static int findNodeAndRm (AVL_T *avl ,NODE** node ,const void * data)
{
    int cmp = 0;
    int ret  = 0;

    NODE* node_rm = NULL;
     if (*node == NULL)
     {
        return 1;
     }

    cmp = avl->comp((*node)->data, data);
    if (0 == cmp)
    {
        if ((*node)->child[LEFT] == NULL && (*node)->child[RIGHT] == NULL  )
        {
            node_rm = (*node);
            *node = NULL;
            free(node_rm);
        }

        else if ((*node)->child[LEFT] == NULL )
        {
           removeNodeOneChild ( node,  LEFT);

        }
         else if ((*node)->child[RIGHT] == NULL )
        {
            removeNodeOneChild ( node,  RIGHT);

        }
        else
        {
            (*node)->data = minNode((*node)->child[RIGHT])->data;
            ret = findNodeAndRm (avl,&(*node)->child[RIGHT], (*node)->data );
        }


        return 0;
    }

    ret = findNodeAndRm (avl,&(*node)->child[cmp < 0], data);
     /* update the new high of the node */
    (*(node))->high = 1+ max_high( (*node)->child[LEFT], (*node)->child[RIGHT]);
    /* check if the balance of the tree has been changed and  if needed to rotate */
    chekRotate ( avl ,*(node) );
    return ret;

}

static void removeNodeOneChild (NODE** node, int diriction)
{
    NODE* node_rm = (*node);
    *node = (*node)->child[!diriction] ;
    free(node_rm);
}

static size_t countNode (NODE * node )
{
    size_t count = 0;
    if (NULL == node )
    {
        return 0 ;
    }
    count = countNode(node->child[LEFT]) + countNode(node->child[RIGHT]);
    return (count+1);
}

static int AVLForEachHelper (NODE * node , ACTION_T action, void *param )
{

    if (NULL == node)
    {
        return 0;
    }
    return ( AVLForEachHelper (node->child[LEFT] ,action, param) ||
             action (node->data ,param) ||
            AVLForEachHelper(node->child[RIGHT] ,action, param ));

}



static int nodeInsert(AVL_T *avl, NODE* new_node ,NODE ** curr_node)
{
    int cmp_ans= 0;
	int ret = 0;
    if (*curr_node == NULL)
    {
        *curr_node = new_node;
        return 0;
    }
    cmp_ans = avl->comp( (*curr_node)->data, new_node->data);
    if (cmp_ans == 0)
    {
        free(new_node);
        return 1;
    }

            /* check to which way needed to insert the new node */
       ret = nodeInsert(avl,new_node, &(*curr_node)->child[cmp_ans < 0]);
       /* update the new high of the node */
       (*(curr_node))->high = 1+ max_high( (*curr_node)->child[LEFT], (*curr_node)->child[RIGHT]);
        /* check if the balance of the tree has been chenge and  if needed to rotate */
       chekRotate ( avl ,*(curr_node) );

    return ret;

}

  /* check if the balance of the tree has been chenge and  if needed to rotate */
static void chekRotate (AVL_T *avl ,NODE * root )
{

    int balance = 0 ;
    /*check if need to rotate */

    balance =  getBalance (root);

       if (balance == -2)
       {
            balance =  getBalance (root->child[RIGHT]);

            if ( balance == 0 || balance == -1  )
            {
                RR(root);
            }
            else
            {
                  RL(root);
            }
       }

       else if ( balance == 2)
       {
            balance =  getBalance (root->child[LEFT]);

            if ( balance == 0  || balance == 1 )
            {
                LL(root);
            }
            else
            {
                  LR(root);
            }
       }


}
static void destroyNode(NODE* node)
{
    if (node !=   NULL)
    {
        destroyNode(node->child[LEFT]);
        destroyNode(node->child[RIGHT]);
        free(node);
    }


}

/****************print function (only for debug)**********************/

static int getNodeHigh(NODE* node)
{
    int x = 0;
    if (NULL == node)
    {
        x= -1 ;
    }
    else
    {
       x =  node->high;
    }

    return x;
}
static int max_high (NODE* node_1 ,  NODE* node_2)
{
    int num_1 = getNodeHigh(node_1);
    int num_2 = getNodeHigh(node_2);

    return  ((num_1 > num_2) ? num_1 : num_2 );
}

static NODE* minNode (NODE * node)
{
    if (node->child[LEFT] == NULL)
        return node;

    return minNode (node->child[LEFT]);
}


/*********************rotate functions****************************************/

/* rotate RR */
NODE * RR(NODE *node)
{
    node = rotate(node, LEFT);
    return(node);
}

/* rotate RL */
static NODE * RL(NODE *node)
{
    node->child[RIGHT] = rotate(node->child[RIGHT], RIGHT);
    node = rotate(node , LEFT);
    return(node);
}

static NODE * LL(NODE *node)
{
    node = rotate (node, RIGHT);
    return(node);
}

static NODE * LR(NODE *node)
{
    node->child[LEFT] = rotate (node->child[LEFT], LEFT);
    node = rotate(node , RIGHT);

    return(node);
}
static NODE* rotate (NODE * root, int direction )
{

    NODE* pivot = root->child[!direction] ;

        /* rotate the root to right */
    root->child[!direction] = pivot->child[!direction] ;
    pivot->child[!direction] =  pivot->child[direction] ;
    pivot->child[direction] = root->child[direction];
    root->child[direction] = pivot ;
    swapData (root , pivot );

    /* set the high of the node after chenge*/
    pivot->high = 1 + max_high(pivot->child[LEFT] , pivot->child[RIGHT] );
    root->high = 1 + max_high(root->child[LEFT] , root->child[RIGHT] );

    return (root);
}


/*swap data of node */
static void swapData (NODE* node_1, NODE* node_2)
{
    void* data = node_1->data;
    node_1->data = node_2->data;
    node_2->data = data;
}

/* return the balance of the node */
static int getBalance (NODE *node)
{
    int high_left = 0;
    int high_right = 0;

    high_left = getNodeHigh(node->child[LEFT]);
    high_right = getNodeHigh(node->child[RIGHT]);

     return  (high_left - high_right);
}

#ifndef NDEBUG
/* Function to line by line print level order traversal a tree*/
static void printLevelOrder( NODE* root)
{
    int h = root->high+1;
    int i;
    int space = 0;
    for (i=1; i<=h; i++)
    {
        for (space = ( h/2) -i ;space >0 ; space-- )
            printf("  ");

        printGivenLevel(root, i);
        printf("\n");
    }
}

/* Print nodes at a given level */
static void printGivenLevel(NODE* root, int level)
{
    int space = 0;
    if (root == NULL)
        return;
    if (level == 1)
    {
    for (space = root->high ;space >=0 ; space-- )
            printf("   ");

        printf("%d", *(int*)root->data);
    }
    else if (level > 1)
    {
        printGivenLevel(root->child[LEFT], level-1);
        printGivenLevel(root->child[RIGHT], level-1);
    }
}

void print_n(AVL_T *avl)
{
    printNode(avl->root);
    printf ("\n");
    printLevelOrder(avl->root);

}
static void printNode(NODE* node)
{
    int x = 0;
    int high = 0;
    if (NULL !=  node)
    {
        high = node->high;
        x = *(int*)node->data;
        printNode(node->child[LEFT]);
        printNode(node->child[RIGHT]);
        printf(" %d high = %d \n", x, high);
    }
}
#endif 
