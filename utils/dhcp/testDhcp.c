
#include <stdio.h> /*printf*/
#include <arpa/inet.h> /*inet_ntoa*/

#include "dhcp.h"

DHCP_T *dhcp;

struct in_addr ip_addr;

unsigned int ip = 0;

static unsigned char firstIp[] = "191.121.1.0/30" ;
static void testCreate();
static void testGetAddress ();
static void testDHCPRelease ();

int main(int argc, char *argv[])
{

    testCreate();
    testGetAddress ();
    testDHCPRelease ();
    printf("\n try again to get address after release \n\n");
    testGetAddress ();
    DHCPDestroy(dhcp);



    return 0;
}

static void testCreate()
{
    dhcp = DHCPCreate(firstIp);
    if (NULL == dhcp)
    {
        printf( "\n testCreate failed  \n" );
    }
    else
    {
        printf( "\n testCreate success  \n" );
    }
}
static void testGetAddress ()
{
     int ret = -1;

    ip=0;
     ret = DHCPGetAddress(dhcp, &ip);
     ip_addr.s_addr = ip;
     if (ret == 0 )
     {
         printf(" successes to get ip-  %s \n",inet_ntoa(ip_addr) );
     }
     else
        printf(" failed to get ip-  %s \n",inet_ntoa(ip_addr) );


    ip=0;
    ret = DHCPGetAddress(dhcp, &ip);
    ip_addr.s_addr = ip;
     if (ret == 0 )
     {
         printf(" successes to get ip-  %s \n",inet_ntoa(ip_addr) );
     }
     else
        printf(" failed to get ip-  %s \n",inet_ntoa(ip_addr) );

    ip=-1;
    ret = DHCPGetAddress(dhcp, &ip);
    ip_addr.s_addr = ip;
     if (ret == 0 )
     {
         printf(" successes to get ip-  %s \n",inet_ntoa(ip_addr) );
     }
     else
        printf(" failed to get ip-  %s \n",inet_ntoa(ip_addr) );



/* if no more space
     ip=0;
     ret = DHCPGetAddress(dhcp, &ip);
     ip_addr.s_addr = ip;
     if (ret == 1 )
     {
         printf(" successes - need to failed get ip-  %s \n",inet_ntoa(ip_addr));
     }
     else
    printf(" failed - need to failed get ip-   %s \n",inet_ntoa(ip_addr));
*/

}

static void testDHCPRelease ()
{
     int ret = -1;
     unsigned int ipRelese = 1;

     printf(" ---------testDHCPRelease--------------- \n" );
     ret = DHCPRelease(dhcp, ipRelese);
     printf(" ---------relese ip  1 --------------- \n" );
     if (ret == 0 )
     {
         printf(" successes to Release ip-  %x \n",ipRelese );
     }
     else
        printf(" failed to Release ip-  %x \n",ipRelese );


     ipRelese = 3;
     ret = DHCPRelease(dhcp, ipRelese);
     printf(" \n---------relese ip  5 (not exises)--------------- \n" );
     if (ret == 0 )
     {
         printf(" successes to Release (not need to successes)ip-  %x \n",ipRelese );
     }
     else
        printf(" failed to Release ip- (need to fail) %x \n",ipRelese );
}

