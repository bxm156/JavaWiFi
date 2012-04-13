/*
 * jwlib.c
 *
 *  Created on: Apr 1, 2012
 *      Author: bryan
 */
#include "jwlib.h"

#include <stdio.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <net/if.h>
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
