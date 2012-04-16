/*
 * jwlib.h
 *
 *  Created on: Apr 1, 2012
 *      Author: bryan
 */

#ifndef JWLIB_H_
#define JWLIB_H_
#include <string>
#include <vector>
#include "asm/types.h"


/* Standard headers */
#include <sys/types.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>		/* gethostbyname, getnetbyname */
#include <net/ethernet.h>	/* struct ether_addr */
#include <sys/time.h>		/* struct timeval */
#include <unistd.h>

/* This is our header selection. Try to hide the mess and the misery :-(
 * Don't look, you would go blind ;-)
 * Note : compatibility with *old* distributions has been removed,
 * you will need Glibc 2.2 and older to compile (which means
 * Mandrake 8.0, Debian 2.3, RH 7.1 or older).
 */

/* Set of headers proposed by Dr. Michael Rietz <rietz@mail.amps.de>, 27.3.2 */
#include <net/if_arp.h>		/* For ARPHRD_ETHER */
#include <sys/socket.h>		/* For AF_INET & struct sockaddr */
#include <netinet/in.h>         /* For struct sockaddr_in */
#include <netinet/if_ether.h>

/* Fixup to be able to include kernel includes in userspace.
 * Basically, kill the sparse annotations... Jean II */
#ifndef __user
#define __user
#endif

#include <linux/types.h>		/* for "caddr_t" et al		*/

/* Glibc systems headers are supposedly less problematic than kernel ones */
#include <sys/socket.h>			/* for "struct sockaddr" et al	*/
#include <net/if.h>			/* for IFNAMSIZ and co... */
#include "wireless.22.h"

//Defile locations on file system to read interface lists
#define PROC_NET_WIRELESS	"/proc/net/wireless"
#define PROC_NET_DEV		"/proc/net/dev"

int jw_parse_proc_interface(char *result, char *buffer, int bufferSize);
std::vector<std::string> jw_enumate_interfaces(const char *proc_net);
int iw_sockets_open(void);
inline int iw_get_ext(int skfd, const char *ifname, int request, struct iwreq pwrq);
std::string jw_get_essid(int skfd, const char *interfaceName);
std::string jw_get_hardware_address(int skfd, const char *interfaceName);
float jw_get_frequency(int skfd, const char *interfaceName);

#endif /* JWLIB_H_ */
