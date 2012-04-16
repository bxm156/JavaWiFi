package com.bryanmarty.javawifi;

public class SystemInterface {
	
	static {
		System.loadLibrary("JavaWiFi");
	}
	private static String interfaceName_;
	
	//Native Methods
	private native boolean nativeInterfaceExists(String interfaceName);
	private native boolean nativeInterfaceIsWiFi(String interfaceName);
	private native String nativeInterfaceGetSSID(String interfaceName);
	private native String nativeInterfaceGetHardwareAddress(String interfaceName);
	private native float nativeInterfaceGetFrequency(String interfaceName);
	
	public SystemInterface(String interfaceName) {
		interfaceName_ = interfaceName;
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
	
	public String getHardwareAddress() {
		return nativeInterfaceGetHardwareAddress(interfaceName_);
	}
	
	public float getFrequency() {
		return nativeInterfaceGetFrequency(interfaceName_);
	}
	
}
