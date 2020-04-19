#include <string.h> /*strtok*/
#include <stdlib.h> /* malloc*/
#include <string.h> /*strtok */


#include "dhcp.h"
#define IPSIZE 32 /* size of ip*/
/* Opaque DHCP structure */
typedef struct node
{
    char status ;
    struct node *child[2];

}NODE_T;

struct dhcp
{
    NODE_T *root;
    size_t available_ip;
    unsigned int subnet_size;
    unsigned int subnet_num;
    unsigned int myip;

} ;

static  char copyStr[64]; /* for copy the const string of ip */
/* get string and return unsigend int */
static void setIp(DHCP_T * dhcp , const unsigned char *subnetAddr);

static NODE_T * nodeCreate ();
/*set on the bit in the index place of the address number */
static void setBit ( unsigned int *address ,int index , int bitValue);
/*get the bit in the index place of the address number */
static unsigned int getBit ( unsigned int *address ,int index);
/*set to bits zero from index place the address number */
static void setAddress ( unsigned int *address ,int index);
/* set the status of node */
static void setStatus (NODE_T * node );
/* get the status of node */
static int getStatus (NODE_T * node );

static int trieCreateAddress (NODE_T * node  , unsigned int *address ,int index );

static void DHCPDestroyHelper (NODE_T * node);

/****************************************************************/
/* Creates a DHCP repository based on 'subnetAddr'.
   The format of 'subnetAddr' should be '192.168.0.0/24',
   for example.
   Returns a DHCP_T instance on success.
   Returns NULL on failure. */
DHCP_T *DHCPCreate(const unsigned char *subnetAddr)
{
    unsigned int ip =0;
    DHCP_T * dhcp = NULL;

        dhcp = calloc(1, sizeof(*dhcp) );
        if (NULL == dhcp)
        {
            return NULL;
        }
        dhcp->root = nodeCreate();

        /* set all the dhcp variable */
        setIp(dhcp , subnetAddr);

        dhcp->available_ip = 1<< (IPSIZE - dhcp->subnet_size );

        /* set 3 address for self use */
        ip =0;
        DHCPGetAddress(dhcp, &ip);
        ip = -1;
        DHCPGetAddress(dhcp, &ip);
        ip = ~1;
        DHCPGetAddress(dhcp, &ip);
        dhcp->myip = ip;



    return dhcp;
}

/* Allocates an IP according to 'ip': if ip is 0, the function
   will attempt to allocate the next available IP address.
   If 'ip' is initialized to any other value, the function will
   attempt to allocate that specific IP address (or the next
   avilable address after ip).
   Returns 0 for success. The allocated address will be placed
   in 'ip'.
   Returns non-zero erro code for failure. */
int DHCPGetAddress(DHCP_T *dhcp, unsigned int *ip)

{

    int success = 0;

    *ip <<= dhcp->subnet_size;
    *ip >>= dhcp->subnet_size;

    success = trieCreateAddress (dhcp->root  , ip ,(IPSIZE - dhcp->subnet_size));
    /* set the mask */
    if (success == 0)
    {
        *ip = *ip | dhcp->subnet_num;
        dhcp->available_ip--;
    }

return success;
}
/* De-allocates the address in 'ip'.
   Returns 0 for success.
   Returns non-zero error code for failure. */

int DHCPRelease(DHCP_T *dhcp, unsigned int ip)
{
    int index = 0;
    int bit = 0;
    NODE_T * node = NULL;

    index = (IPSIZE -  dhcp->subnet_size ) ;
    node = dhcp->root;

        /* loop for set status of the ip release way*/
    while (node !=  NULL)
    {
        bit = getBit(&ip , index - 1) ;
        node->status = 0;
        node = node->child[bit];
        index--;
    }

    index++;
    /* if release successes update the availavle ip*/

    if (index == 0)
    {
        dhcp->available_ip++;
    }
    return index ;
}

/* Releases the resources used by the 'dhcp'. */
void DHCPDestroy(DHCP_T *dhcp)
{
    DHCPDestroyHelper(dhcp->root);
    free(dhcp);
}

/* Returns number of available IP addresses in 'dhcp' */
size_t DHCPFreeSpace(const DHCP_T *dhcp)
{
    return dhcp->available_ip;
}
/*********************static function ***************************************/

static void DHCPDestroyHelper (NODE_T * node)
{
    if (node !=  NULL)
        {
            DHCPDestroyHelper(node->child[0]);
            DHCPDestroyHelper(node->child[1]);
            free(node);
        }
}
static NODE_T * nodeCreate ()
{
    NODE_T * node = NULL;
    /*check of allocate success*/
    node =  calloc (1,sizeof(*node));
    if (NULL == node)
    {
        return NULL;
    }

    return node;
}


static void setIp(DHCP_T * dhcp , const unsigned char *subnetAddr)
{
        char *token;
        int i = 0;
        int subnet = 0;
        unsigned int ip =0;


        strcpy(copyStr,(char *)subnetAddr );
        /* get the first token */
        token = strtok(copyStr,"./");
        ip = atoi(token);

        for (i =0; i<3 ; i++)
        {
            token = strtok(NULL, "./");
            ip = ip<<8;
            ip |= atoi(token);
        }

        token = strtok(NULL, "./");

        subnet = atoi(token);
        dhcp->subnet_size =subnet;

        /*set the subnet number (set to zero the other digit)*/
        ip &= ((1 << subnet) - 1) << (IPSIZE - subnet);
        /* ip >>= (32- subnet ); */
        dhcp->subnet_num = ip;

    return ;
}
/* recortion func to get address  */
static int trieCreateAddress (NODE_T * node  , unsigned int *address ,int index )
{
    int bit = 0;
    int ret =1;
    if (index == 0 )
    {
        node->status=1;
        return 0;
    }
    /* get the direction  */
    bit = getBit(address , index-1) ;

    if (0 == getStatus( node->child[bit]))
    {
        if (node->child[bit]== NULL)
        {
            node->child[bit] = nodeCreate();
            /* check if allocate success */
            if (NULL ==node->child[bit])
            {
                return 1;
            }
        }

       ret = trieCreateAddress (node->child[bit]  ,  address , index-1 );
    }
    else if (0 == getStatus( node->child[!bit]))
    {

        setAddress (address , index -1 );
        setBit(address , index-1, !bit );

        if (node->child[!bit]== NULL)
        {
            node->child[!bit] = nodeCreate();
            /* check if allocate success */
            if (NULL == node->child[bit])
            {
                return 1;
            }
        }
       ret = trieCreateAddress (node->child[!bit]  ,  address , index-1 );
    }

    setStatus (node);
    return ret;
}


static void setBit ( unsigned int *address ,int index , int bitValue)
{

    *address ^= 1<<index;
}

static unsigned int getBit ( unsigned int *address ,int index)
{
    unsigned int  mask = 0;
    mask =  1<<index ;
    return ((*address & mask) ? 1 : 0);
}

static void setAddress ( unsigned int *address ,int index)
{
    *address >>= index;
     *address <<= index;
}
static void setStatus (NODE_T * node )
{

    if (getStatus(node->child[0]) ==1 && getStatus(node->child[1]) ==1  )
        node->status= 1  ;
    else
        node->status= 0 ;
}

static int getStatus (NODE_T * node )
{
    if (NULL == node )
        return 0;
    return node->status;
}


