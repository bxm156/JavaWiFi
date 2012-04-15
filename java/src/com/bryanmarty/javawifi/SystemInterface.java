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
		String essid = nativeInterfaceGetSSID(interfaceName_);
		if(essid != null) {
			return essid;
		}
		return "I detected a null";
	}
	
}
