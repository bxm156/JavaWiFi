package com.bryanmarty.javawifi;

import sun.org.mozilla.javascript.NativeArray;

public class SystemInterface {
	
	static {
		System.loadLibrary("JavaWiFi");
	}
	private static String interfaceName_;
	
	//Native Methods
	private static native String[] nativeInterfaceGetAllInterfaceNames(boolean includeWiFi);
	private native boolean nativeInterfaceExists(String interfaceName);
	private native boolean nativeInterfaceIsWiFi(String interfaceName);
	private native String nativeInterfaceGetSSID(String interfaceName);
	private native String nativeInterfaceGetNickname(String interfaceName);
	private native String nativeInterfaceGetHardwareAddress(String interfaceName);
	private native float nativeInterfaceGetFrequency(String interfaceName);
	private native int nativeInterfaceGetBitRate(String interfaceName);
	
	public SystemInterface(String interfaceName) {
		interfaceName_ = interfaceName;
	}
	
	public static String[] getAllInterfaceNames() {
		return nativeInterfaceGetAllInterfaceNames(true);
	}
	
	public static String[] getAllInterfaceNames(boolean includeWiFi) {
		return nativeInterfaceGetAllInterfaceNames(includeWiFi);
	}
	
	@Override
	public String toString() {
		return interfaceName_;
	}
	
	public boolean exists() {
		return nativeInterfaceExists(interfaceName_);
	}
	
	public boolean isWiFi() {
		return nativeInterfaceIsWiFi(interfaceName_);
	}
	
	public String getSSID() {
		return nativeInterfaceGetSSID(interfaceName_);
	}
	
	public String getNickname() {
		return nativeInterfaceGetNickname(interfaceName_);
	}
	
	public String getHardwareAddress() {
		return nativeInterfaceGetHardwareAddress(interfaceName_);
	}
	
	public float getFrequency() {
		return nativeInterfaceGetFrequency(interfaceName_);
	}
	
	public int getBitRate() {
		return nativeInterfaceGetBitRate(interfaceName_);
	}
	
}
