/*
 * systemInterface.c
 *
 *  Created on: Mar 31, 2012
 *      Author: bryan
 */
#include "jwlib.h"
#include "systemInterface.h"
#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "string.h"
/*
 * Class:     com_bryanmarty_javawifi_SystemInterface
 * Method:    nativeInterfaceExists
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_bryanmarty_javawifi_SystemInterface_nativeInterfaceExists
  (JNIEnv * env, jobject obj, jstring interfaceName) {

	jboolean exists = JNI_FALSE;

	const char *iName = env->GetStringUTFChars(interfaceName, NULL);
	if(iName == NULL) {
		return exists;
	}

	std::vector<std::string> interfaces = jw_enumate_interfaces(PROC_NET_DEV);
	for(unsigned int i = 0; i < interfaces.size(); i++) {
		const char *name = interfaces[i].c_str();
		if(strcmp(name,iName) == 0) {
			exists = JNI_TRUE;
		}
	}

	env->ReleaseStringUTFChars(interfaceName,iName);

	return exists;
}

/*
 * Class:     com_bryanmarty_javawifi_SystemInterface
 * Method:    nativeInterfaceIsWiFi
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_bryanmarty_javawifi_SystemInterface_nativeInterfaceIsWiFi
  (JNIEnv * env, jobject obj, jstring interfaceName) {
		jboolean isWiFi = JNI_FALSE;

		const char *iName = env->GetStringUTFChars(interfaceName, NULL);
		if(iName == NULL) {
			return isWiFi;
		}

		std::vector<std::string> interfaces = jw_enumate_interfaces(PROC_NET_WIRELESS);
		for(unsigned int i = 0; i < interfaces.size(); i++) {
			const char *name = interfaces[i].c_str();
			if(strcmp(name,iName) == 0) {
				isWiFi = JNI_TRUE;
			}
		}

		env->ReleaseStringUTFChars(interfaceName,iName);

		return isWiFi;
}

JNIEXPORT jstring JNICALL Java_com_bryanmarty_javawifi_SystemInterface_nativeInterfaceGetSSID
  (JNIEnv * env, jobject obj, jstring interfaceName) {

	const char *iName = env->GetStringUTFChars(interfaceName, NULL);
	if(iName == NULL) {
		return NULL;
	}
	int skfd;
	if((skfd = iw_sockets_open()) < 0) {
		return NULL;
	}

	std::string essid = jw_get_essid(skfd,iName);

	close(skfd);

	env->ReleaseStringUTFChars(interfaceName,iName);

	jstring result = env->NewStringUTF(essid.c_str());
	return result;
}

JNIEXPORT jstring JNICALL Java_com_bryanmarty_javawifi_SystemInterface_nativeInterfaceGetHardwareAddress
  (JNIEnv * env, jobject obj, jstring interfaceName) {
	const char *iName = env->GetStringUTFChars(interfaceName, NULL);
	if(iName == NULL) {
		return NULL;
	}
	int skfd;
	if((skfd = iw_sockets_open()) < 0) {
		return NULL;
	}

	std::string essid = jw_get_hardware_address(skfd,iName);

	close(skfd);

	env->ReleaseStringUTFChars(interfaceName,iName);

	jstring result = env->NewStringUTF(essid.c_str());
	return result;
}


