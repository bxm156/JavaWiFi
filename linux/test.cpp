/*
 * test.c
 *
 *  Created on: Apr 3, 2012
 *      Author: bryan
 */

#include "jwlib.h"
#include "stdio.h"

int main(int argc, char *argv[]) {
	std::vector<std::string> results = jw_enumate_interfaces(PROC_NET_DEV);
	for(unsigned int i=0; i < results.size(); i++) {
		std::string name = results[i];
		printf("%s\n",name.c_str());
	}
	return 0;
}


