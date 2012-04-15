/*
 * jwlib.c
 *
 *  Created on: Apr 1, 2012
 *      Author: bryan
 */
#include "jwlib.h"

#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <string.h>
#include <string>

std::vector<std::string> jw_enumate_interfaces(const char *proc_net) {

	std::vector<std::string> results;

	char buffer[1024];
	FILE *pFile;
	pFile = fopen(proc_net,"r");
	if(pFile != NULL) {
		//Read 2 lines of header data
		fgets(buffer, sizeof(buffer), pFile);
		fgets(buffer, sizeof(buffer), pFile);

		//char interface_array[][IFNAMSIZ];

		while(fgets(buffer,sizeof(buffer),pFile)) {
			//Skip blank lines
			if(buffer[0] == '\0' || buffer[1] == '\0') {
				continue;
			}
			//Declare a place to store the name of the interface
			char name[IFNAMSIZ + 1];

			if(jw_parse_proc_interface(name,buffer,sizeof(buffer)) == 0) {
				//Parse successful
				results.push_back(name);
			} else {
				//Parse unsuccessful
				printf("Parse Failed\n");
			}

		}
		fclose(pFile);
	}
	return results;


}

int jw_parse_proc_interface(char *result, char *buffer, int bufferSize) {
	char *end;
	//Skip leading whitepsace
	while(isspace(*buffer)) {
		buffer++;
	}
	end = strrchr(buffer,':');
	// Not found ???  OR To big ???
	if((end == NULL) || (((end - buffer) + 1) > bufferSize)) {
		return -1;
	}
	memcpy(result,buffer,(end-buffer));
	result[end-buffer] = '\0';
	return 0;
}

/*
 * Open a socket.
 * Depending on the protocol present, open the right socket. The socket
 * will allow us to talk to the driver.
 */
int
iw_sockets_open(void)
{
  static const int families[] = {
    AF_INET, AF_IPX, AF_AX25, AF_APPLETALK
  };
  unsigned int	i;
  int		sock;

  /*
   * Now pick any (exisiting) useful socket family for generic queries
   * Note : don't open all the socket, only returns when one matches,
   * all protocols might not be valid.
   * Workaround by Jim Kaba <jkaba@sarnoff.com>
   * Note : in 99% of the case, we will just open the inet_sock.
   * The remaining 1% case are not fully correct...
   */

  /* Try all families we support */
  for(i = 0; i < sizeof(families)/sizeof(int); ++i)
    {
      /* Try to open the socket, if success returns it */
      sock = socket(families[i], SOCK_DGRAM, 0);
      if(sock >= 0)
	return sock;
  }

  return -1;
}


/*------------------------------------------------------------------*/
/*
 * Wrapper to extract some Wireless Parameter out of the driver
 */
inline int iw_get_ext(int			skfd,		/* Socket to the kernel */
	   const char *		ifname,		/* Device name */
	   int			request,	/* WE ID */
	   struct iwreq *	pwrq)		/* Fixed part of the request */
{
  /* Set device name */
  strncpy(pwrq->ifr_name, ifname, IFNAMSIZ);
  /* Do the request */
  return(ioctl(skfd, request, pwrq));
}


std::string jw_get_essid(int skfd, const char *interfaceName) {

	struct iwreq		wrq;

	  /* Get wireless name */
	  if(iw_get_ext(skfd, interfaceName, SIOCGIWNAME, &wrq) < 0) {
	    /* If no wireless name : no wireless extensions */
	    return NULL;
	  }

	  char buffer[IW_ESSID_MAX_SIZE + 1];
	  wrq.u.essid.pointer = (caddr_t) buffer;
	  wrq.u.essid.length = IW_ESSID_MAX_SIZE + 1;
	  wrq.u.essid.flags = 0;
	  if(iw_get_ext(skfd, interfaceName, SIOCGIWESSID, &wrq) >= 0) {
		 return buffer;
	  } else {
		  return NULL;
	}
}

std::string jw_get_hardware_address(int skfd, const char *interfaceName) {
	struct ifreq req;

	 strncpy(req.ifr_ifrn.ifrn_name, interfaceName, IFNAMSIZ);

	if(ioctl(skfd,SIOCGIFHWADDR,&req) >= 0) {
		char buffer[18];
		sprintf(buffer,"%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",
		         (unsigned char)req.ifr_ifru.ifru_hwaddr.sa_data[0],
		         (unsigned char)req.ifr_ifru.ifru_hwaddr.sa_data[1],
		         (unsigned char)req.ifr_ifru.ifru_hwaddr.sa_data[2],
		         (unsigned char)req.ifr_ifru.ifru_hwaddr.sa_data[3],
		         (unsigned char)req.ifr_ifru.ifru_hwaddr.sa_data[4],
		         (unsigned char)req.ifr_ifru.ifru_hwaddr.sa_data[5]);
		return buffer;
	}
	return NULL;
 }
