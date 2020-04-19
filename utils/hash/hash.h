#ifndef __HASH_H__
#define __HASH_H__

#include <stddef.h>		/*	size_t	*/


/*	Opaque Hash structure	*/
typedef struct hash HASH_T;

/*	Action function, which receives an element in an hash and
	returns 0 for success and non-zero otherwise.						*/
typedef int (* ACTION_F)( void *data, void *param);

/*	hush function, which receives a key and returns index				*/
typedef size_t (* HASH_F)(const void *data);

/*	Comparison function: Returns a positive integer if data1 > data2,
	a negative integer if data1 < data2 and 0 if data1 == data2.		*/
typedef int (* COMP_F) (const void *data1, const void *data2);


/*	Creates a hash table		*/
HASH_T *HashCreate(HASH_F getHash, COMP_F cmp, size_t table_size);

/*	Disposes of the resources used by hash								*/
void HashDestroy(HASH_T *hash);

/*	Inserts 'data' into the hash. Returns 0 if successful.
	Returns non-zero otherwise. */
int HashInsert(HASH_T *hash, const void *data);

/*	Removes 'data' from hash. Returns 0 if 'data' was found in hash.
	Returns non-zero otherwise. */
int HashRemove(HASH_T *hash, const void *data);

/*	Returns the number of items in the hash								*/
size_t HashSize(const HASH_T *hash);

/*	Returns 1 if hash is empty, 0 otherwise								*/
int HashIsEmpty(const HASH_T *hash);

/* Returns an element, which matches 'data'.
   If the element is not found, returns NULL. 							*/
void *HashFind(const HASH_T *hash, const void *data);

/*	Executes function 'action' on each element in hash (as long as
	'action' returns success). Returns 0 for success, non-zero
	otherwise. 'param' is an optional parameter passed into 'action'.	*/
int HashForEach(HASH_T *hash,  ACTION_F action, void *param);

#endif /* __HASH_H__ */
