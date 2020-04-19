#include<stdio.h>
#include <arpa/inet.h>


#include "dhcp.h"   /*dhcp.h*/

static struct in_addr addr;



void create_test(DHCP_T* dhcp);
void getAddres_test(DHCP_T* dhcp);
void relese_test(DHCP_T* dhcp);



int main()
{

    DHCP_T* dhcp = NULL;
    const char* add = "123.144.0.0/16";

    dhcp = DHCPCreate((const unsigned char*)add);

    create_test(dhcp);
    getAddres_test(dhcp);

    relese_test(dhcp);


    DHCPDestroy(dhcp);

    return 0;
}


void create_test(DHCP_T* dhcp)
{

    printf("\n create_test \n");
     if (NULL == dhcp)
     {
         printf("error\n");
     }
     else
    {
        printf("succes\n");
    }



}

void  getAddres_test(DHCP_T* dhcp)
{

    unsigned int add = 0;
    unsigned int* add_ptr = &add;

    printf("\n getAddres_test \n");


    DHCPGetAddress(dhcp,add_ptr);

    addr.s_addr = add;



    printf("%s \n", inet_ntoa(addr));



    add = 0;
    DHCPGetAddress(dhcp,add_ptr);
    addr.s_addr = add;
    printf("%s \n", inet_ntoa(addr));

    add = 0;
    DHCPGetAddress(dhcp,add_ptr);
    addr.s_addr = add;
    printf("%s \n", inet_ntoa(addr));


    add = 15;
    DHCPGetAddress(dhcp,add_ptr);
    addr.s_addr = add;
    printf("%s \n", inet_ntoa(addr));



    add = 15;
    DHCPGetAddress(dhcp,add_ptr);
    addr.s_addr = add;
    printf("%s \n", inet_ntoa(addr));


     add = 13;
    DHCPGetAddress(dhcp,add_ptr);
    addr.s_addr = add;
    printf("%s \n", inet_ntoa(addr));

    add = -1;
    DHCPGetAddress(dhcp,add_ptr);
    addr.s_addr = add;
    printf("%s \n", inet_ntoa(addr));

    add = -1;
    DHCPGetAddress(dhcp,add_ptr);
    addr.s_addr = add;
    printf("%s \n", inet_ntoa(addr));

    add = -1;
    DHCPGetAddress(dhcp,add_ptr);
    addr.s_addr = add;
    printf("%s \n", inet_ntoa(addr));



}




void relese_test(DHCP_T* dhcp)
{
    unsigned int add = 13;
    unsigned int* add_ptr = &add;
    int ret1 =0 ;
    int ret2 =0 ;

    DHCPRelease(dhcp, 13);

    printf("\n relese_test \n");

    DHCPGetAddress(dhcp,add_ptr);
    addr.s_addr = add;
    printf("%s \n", inet_ntoa(addr));

    DHCPRelease(dhcp, 2);
    add = 2;

     DHCPGetAddress(dhcp,add_ptr);
    addr.s_addr = add;
    printf("%s \n", inet_ntoa(addr));

    ret1 = DHCPRelease(dhcp, 0);
    ret2 = DHCPRelease(dhcp, (unsigned int)-1);

    if(ret1 == -1 && ret2 == -1)
    {
        printf("\n can't release the 0.0.0.0  or the 255.255.255.255 ip \n");
    }

}
