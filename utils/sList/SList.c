#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "SList.h"


/*	promote the head to the next node in n time */
static Node_t* distance (Node_t* head, size_t n);

/* create a node and returns the new node pointer  */
Node_t* SListCreate(void *data)
{
	
	Node_t *n= NULL;
	
	n =(Node_t *) calloc (1, sizeof(Node_t));
		/* check if alloce succes */
		
	if ( NULL == n)
	{
		return NULL;
	}
	n->data = data;	
	return n;
}

/* new head will point to head - returns new head pointer or NULL */
Node_t* SListInsert(Node_t *head, Node_t *new_head)
{

	void * temp_data = head->data;
	
	assert ( NULL != new_head);
	
	head->data = new_head->data;
	new_head->data = temp_data;
	head->next = new_head;
	
	return head;
}



/* head will point to new node, new node will point to head's former next node, returns head pointer  */ 
Node_t* SListInsertAfter(Node_t *new_node, Node_t *head)
{
	assert ( NULL != new_node && NULL != head);
	
	new_node->next = head->next;
	head->next = new_node;
	
	return head;
}

/* swap node's data with node's data, node next pointer will point to the next-next pointer*/
/* returns next pointer for release without data loss or self node in case next is NULL  */
Node_t* SListRemove(Node_t* node)
{

	
	void * temp_data = NULL;
	Node_t* next_node = NULL;
	
	assert (NULL != node);
	/* if the node is the last node in the list */
	/* we do nothing and return the node himself*/
	if ( NULL == node->next)
	{
		return node;
	}
		
	next_node = node -> next;
	temp_data = node-> data;
	
	*node = *node->next;
	
	next_node->data = temp_data;

	/* return the free node */
	return next_node;
}

/* removes the node after delivered node, returns deleted node (for free) */
Node_t* SListRemoveAfter(Node_t *node)
{
	
	Node_t* next_node = node->next;
	
	assert (NULL != node);
	/*check if node after is null */
	if ( NULL == node->next)
	{
		return NULL;
	}
	node->next =  next_node->next;
	
	return next_node;
}


/* User Match_t function should return 1 for find, returns found node pointer or NULL */
Node_t* SListFind(const Node_t* head, Match_t match, void* param)
{
	Node_t *temp = (Node_t *) head;
	
	assert (NULL != head);
	
	while (temp != NULL )
	{
		if (0 == match(temp->data, param))
		{
			return temp;
		}
		temp= temp->next;
	}
	
	return NULL;
}

/* excutes Action_t user function on each node data in the list */ 
int SListForEach(Node_t *head, Action_t act, void *param)
{
	assert (NULL != head);
	
	while(NULL != head)
	{
		if (0 != act(head->data, param) )
			return 1;	
			
		head = head->next;
	}
	return 0;
}

/* countes nodes in list, returns number as size_t */
size_t SListCount( const Node_t* head)
{
	size_t count = 1 ;
		
	assert(head != NULL);
	
	while ( head->next != NULL)
	{
		count++;
		head= head->next;
	}
	
	return count;
}


/* Functino filps the POINTERS in the nodes, so head pointer will be tha last */
/* node in the list after it was flipped. Returns the new head, which was the */
/* last item on the list before the flip.									  */
Node_t* SListFlip(Node_t* head)
{
	Node_t *temp_head; 
	Node_t *temp ;
	Node_t *temp_next ;
	
	assert(NULL != head && NULL != head->next);
	
	temp_head = head; 
	temp = head->next;
	temp_next = head->next->next;
	
	
	head->next = NULL ; /*chenge the first node to point on NULL*/
	while (temp_next != NULL)
	{
		temp->next =  temp_head; /* chenge the pointer*/
							
		temp_head = temp ;	/* update the temp pointer	*/		
		temp = temp_next ;
		temp_next  = temp_next->next ;
		
	}
	
	temp->next = temp_head;
	return temp;
}


/* returns 1 if list has unwanted loop behaviour, else returns 0 */
int SListHasLoop(const Node_t* head)
{
	
	Node_t * temp_one_step = (Node_t*) head;
	Node_t * temp_two_step = (Node_t*) head;
	
	while(temp_two_step != NULL && temp_two_step->next != NULL)
	{
		temp_one_step = temp_one_step->next ;
		temp_two_step = temp_two_step->next->next ;
		
		if (temp_two_step == temp_one_step)
			return 1;
	}
	
	return 0;
}

/* Function gets two lists and see if a node in list 1, also exists in list 2 */
/* Function returns the first node found pointer */
Node_t* SListFindIntersection(const Node_t* head_1, const Node_t* head_2)
{
	
	Node_t * temp_head1 = (Node_t*) head_1;
	Node_t * temp_head2 = (Node_t*) head_2;
	
	size_t len1 = SListCount(temp_head1);
	size_t len2 = SListCount(temp_head2);
	
	
	
	if (len1 > len2)
	{
		temp_head1 = distance (temp_head1, len1 - len2);
	}
	else 
	{
		temp_head2 = distance(temp_head2, len2 - len1);
	}
	
	while (temp_head1 != NULL)
	{
		if (temp_head1 == temp_head2)
		{
			return temp_head1;
		}
		temp_head1 = temp_head1->next;
		temp_head2 = temp_head2->next;
	}
	
	return NULL;
}

/*	promote the head to the next node in n time */
static Node_t* distance (Node_t* head, size_t n)
{
	assert (head != NULL );
	while (n > 0 )
	{
		head = head->next;
		n--;
	}
	return head;
}








