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
#include <set>
#include <algorithm>
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

JNIEXPORT jobjectArray JNICALL Java_com_bryanmarty_javawifi_SystemInterface_nativeInterfaceGetAllInterfaceNames
  (JNIEnv * env, jclass obj) {


	std::vector<std::string> allInterfaces = jw_enumate_interfaces(PROC_NET_DEV);


	/*if(!includeWiFi) {
		std::vector<std::string> allWiFiInterfaces = jw_enumate_interfaces(PROC_NET_WIRELESS);

		std::set<std::string> set_allInterfaces(allInterfaces.begin(), allInterfaces.end());
		std::set<std::string> set_allWiFiInterfaces(allWiFiInterfaces.begin(),allWiFiInterfaces.end());

		std::vector<std::string> difference;

		std::set_difference(set_allInterfaces.begin(),set_allInterfaces.end(),
				set_allWiFiInterfaces.begin(), set_allWiFiInterfaces.end(),
				std::back_inserter(difference));
		allInterfaces = difference;
	}*/

	jobjectArray results;

	results = (jobjectArray)	env->NewObjectArray(allInterfaces.size(),
								env->FindClass("java/lang/String"),
								env->NewStringUTF(""));

	for(unsigned int i = 0; i < allInterfaces.size(); i++ ) {
		env->SetObjectArrayElement(results,i,env->NewStringUTF(allInterfaces[i].c_str()));
	}

	return results;

}

JNIEXPORT jobjectArray JNICALL Java_com_bryanmarty_javawifi_SystemInterface_nativeInterfaceGetAllWiFiInterfaceNames
  (JNIEnv * env, jclass obj) {

	std::vector<std::string> allInterfaces = jw_enumate_interfaces(PROC_NET_WIRELESS);

	jobjectArray results;

	results = (jobjectArray)	env->NewObjectArray(allInterfaces.size(),
								env->FindClass("java/lang/String"),
								env->NewStringUTF(""));

	for(unsigned int i = 0; i < allInterfaces.size(); i++ ) {
		env->SetObjectArrayElement(results,i,env->NewStringUTF(allInterfaces[i].c_str()));
	}

	return results;

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

JNIEXPORT jstring JNICALL Java_com_bryanmarty_javawifi_SystemInterface_nativeInterfaceGetNickname
  (JNIEnv * env, jobject obj, jstring interfaceName) {

	const char *iName = env->GetStringUTFChars(interfaceName, NULL);
	if(iName == NULL) {
		return NULL;
	}
	int skfd;
	if((skfd = iw_sockets_open()) < 0) {
		return NULL;
	}

	std::string essid = jw_get_nickname(skfd,iName);

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

JNIEXPORT jfloat JNICALL Java_com_bryanmarty_javawifi_SystemInterface_nativeInterfaceGetFrequency
  (JNIEnv * env, jobject obj, jstring interfaceName) {
	const char *iName = env->GetStringUTFChars(interfaceName, NULL);
	if(iName == NULL) {
		return NULL;
	}
	int skfd;
	if((skfd = iw_sockets_open()) < 0) {
		return NULL;
	}

	float result = jw_get_frequency(skfd,iName);

	close(skfd);

	env->ReleaseStringUTFChars(interfaceName,iName);

	return result;

}

JNIEXPORT jint JNICALL Java_com_bryanmarty_javawifi_SystemInterface_nativeInterfaceGetBitRate
  (JNIEnv * env, jobject obj, jstring interfaceName) {
	const char *iName = env->GetStringUTFChars(interfaceName, NULL);
	if(iName == NULL) {
		return NULL;
	}

	int skfd;
	if((skfd = iw_sockets_open()) < 0) {
		return NULL;
	}

	int result = jw_get_bit_rate(skfd,iName);

	close(skfd);

	env->ReleaseStringUTFChars(interfaceName,iName);

	return result;

}
