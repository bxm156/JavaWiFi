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

//Defile locations on file system to read interface lists
#define PROC_NET_WIRELESS	"/proc/net/wireless"
#define PROC_NET_DEV		"/proc/net/dev"

int jw_parse_proc_interface(char *result, char *buffer, int bufferSize);
std::vector<std::string> jw_enumate_interfaces(const char *proc_net);

#endif /* JWLIB_H_ */
