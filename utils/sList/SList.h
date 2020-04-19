#ifndef	__SLIST_H__

#define	__SLIST_H__



typedef struct Node

{

	void* data;

	struct Node* next; 

}Node_t;



typedef int (*Match_t)(const void* data, const void* param);



typedef int (*Action_t)(void* data, void* param);



/* create a node and returns the new node pointer  */

Node_t* SListCreate(void* data);



/* new head will point to head - returns new head pointer or NULL */

Node_t* SListInsert(Node_t* head, Node_t* new_head); 



/* head will point to new node, new node will point to head's former next	*/

/* node returns head pointer  												*/ 

Node_t* SListInsertAfter(Node_t* new_node, Node_t* head);



/* swap node's data with node's data, node next pointer will point to the 	*/

/* next-next pointer. returns next pointer for release without data loss or */

/* self node in case next is NULL  											*/

Node_t* SListRemove(Node_t* node);



/* removes the node after delivered node, returns deleted node (for free) */

Node_t* SListRemoveAfter(Node_t* node);



/* User Match_t function should return 1 for find, returns found node pointer or NULL */

Node_t* SListFind(const Node_t* head, Match_t match, void* param);



/* excutes Action_t user function on each node data in the list */ 

int SListForEach(Node_t* head, Action_t, void* param); 



/* countes nodes in list, returns number as size_t */

size_t SListCount(const Node_t* head);



/* Functino filps the POINTERS in the nodes, so head pointer will be tha last */

/* node in the list after it was flipped. Returns the new head, which was the */

/* last item on the list before the flip.									  */

Node_t* SListFlip(Node_t* head);



/* returns 1 if list has unwanted loop behaviour, else returns 0 */
int SListHasLoop(const Node_t* head);



/* Function gets two lists and see if a node in list 1, also exists in list 2 */
/* Function returns the first node found pointer */
Node_t* SListFindIntersection(const Node_t* head_1, const Node_t* head_2);





#endif /* __SLIST_H__ */



