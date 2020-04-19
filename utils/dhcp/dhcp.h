#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h>	/* size_t */

/* Opaque DHCP structure */
typedef struct dhcp DHCP_T;

/* Creates a DHCP repository based on 'subnetAddr'.
   The format of 'subnetAddr' should be '192.168.0.0/24',
   for example.
   Returns a DHCP_T instance on success.
   Returns NULL on failure. */
DHCP_T *DHCPCreate(const unsigned char *subnetAddr);

/* Releases the resources used by the 'dhcp'. */
void DHCPDestroy(DHCP_T *dhcp);

/* Allocates an IP according to 'ip': if ip is 0, the function
   will attempt to allocate the next available IP address.
   If 'ip' is initialized to any other value, the function will
   attempt to allocate that specific IP address (or the next
   avilable address after ip).
   Returns 0 for success. The allocated address will be placed
   in 'ip'.
   Returns non-zero erro code for failure. */
int DHCPGetAddress(DHCP_T *dhcp, unsigned int *ip);

/* De-allocates the address in 'ip'.
   Returns 0 for success.
   Returns non-zero erro code for failure. */
int DHCPRelease(DHCP_T *dhcp, unsigned int ip);

/* Returns number of available IP addresses in 'dhcp' */
size_t DHCPFreeSpace(const DHCP_T *dhcp);

#endif /* __DHCP_H__ */
