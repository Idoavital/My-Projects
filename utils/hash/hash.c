#include <assert.h> /* assert*/
#include <stdlib.h> /* malloc */

#include "hash.h"
#include "AVL.h"

/*	Opaque Hash structure	*/
struct hash
{
    HASH_F key_f;
    COMP_F comp_f;
    size_t size;
    size_t capacity;
    AVL_T *table[1];
};

 /* find the key of the data from the hash function*/
static size_t getHashKey (const HASH_T *hash, const void *data);
/*******************************************************************************/

/*	Creates a hash table		*/
HASH_T *HashCreate(HASH_F getHash, COMP_F cmp, size_t table_size)
{
    HASH_T * hash = NULL;

        /*set to zero all the table cell - cell that not in use must to be null */
    hash = (HASH_T *)calloc (1, offsetof(HASH_T,table) + sizeof (*hash->table) * table_size );

    if (NULL == hash)
    {
        return NULL;
    }

    hash->key_f = getHash ;
    hash->comp_f = cmp;
    hash->capacity = table_size;
    hash->size = 0;

return hash;
}

/*	Disposes of the resources used by hash */
void HashDestroy(HASH_T *hash)
{
    size_t i  = 0;
    assert (NULL != hash);


    for (i = 0 ; i < hash->capacity ; i++)
    {
        if (hash->table[i] != NULL)
        {
            AVLDestroy(hash->table[i]);
        }
    }
    free(hash);

}

/*	Inserts 'data' into the hash. Returns 0 if successful.
	Returns non-zero otherwise. */
int HashInsert(HASH_T *hash, const void *data)
{
    size_t key = 0;
    int ret = 0;

    assert (NULL != hash);
    /* find the key of the data from the hash function*/
    key =getHashKey (hash, data);
    /*check if the cell is free , e.c if its the first insert of this key data */
    if (NULL == hash->table[key])
    {
        /* create avl for the first time */
        hash->table[key] = AVLCreate(hash->comp_f);
        /* check create success */
        if (NULL == hash->table[key] )
        {
            return 1;
        }
    }

    ret = AVLInsert(hash->table[key], data);
    /* check success of insert  */
    if (ret == 0)
    {
        hash->size++;
    }
    return ret;
}

/*	Removes 'data' from hash. Returns 0 if 'data' was found in hash.
	Returns non-zero otherwise. */
int HashRemove(HASH_T *hash, const void *data)
{
    size_t key = 0;
    int ret =0;

    assert (NULL != hash);
    /* find the key of the data from the hash function*/
    key = getHashKey(hash, data);

    /*check if the cell is free , e.g if its the first insert of this key data */
    if (NULL == hash->table[key])
    {
        return 0;
    }
    ret = AVLRemove(hash->table[key],data);
    if (ret == 0)
    {
        hash->size--;
    }
    return ret;
}


/*	Returns the number of items in the hash */
size_t HashSize(const HASH_T *hash)
{
    assert (NULL != hash);
    return (hash->size);
}

/*	Returns 1 if hash is empty, 0 otherwise */
int HashIsEmpty(const HASH_T *hash)
{
    assert (NULL != hash);
    return (!hash->size);
}

/* Returns an element, which matches 'data'.
   If the element is not found, returns NULL. */
void *HashFind(const HASH_T *hash, const void *data)
{
    size_t key = 0;
    assert (NULL != hash);
    /* find the key of the data from the hash function*/
    key = getHashKey(hash, data);

    /*check if the cell is free , e.c if its the first insert of this key data */
    if (NULL == hash->table[key])
    {
        return NULL;
    }

    return (AVLFind(hash->table[key],data));
}

/*	Executes function 'action' on each element in hash (as long as
	'action' returns success). Returns 0 for success, non-zero
	otherwise. 'param' is an optional parameter passed into 'action'.	*/
int HashForEach(HASH_T *hash,  ACTION_F action, void *param)
{
    size_t i  = 0;

    for (i = 0 ; i < hash->capacity ; i++)
    {
        if (hash->table[i] != NULL)
        {
            AVLForEach(hash->table[i], action , param);
        }
    }
    return 0;
}
/************************static function***********************************/

 /* find the key of the data from the hash function*/
static size_t getHashKey (const HASH_T *hash, const void *data)
{
    return (hash->key_f(data));
}














