package com.bryanmarty.javawifi;

import java.util.Hashtable;

import com.bryanmarty.javawifi.exceptions.InvalidSystemInterface;
import com.bryanmarty.javawifi.exceptions.NonexistantSystemInterface;

public class SystemInterface {
	
	static {
		System.loadLibrary("JavaWiFi");
	}
	
	/** Holds the name of the local network interface this object is associated with */
	protected String interfaceName_;
	private static Hashtable<String, ManagedSystemInterface> managedSystemInterfaces = new Hashtable<String,ManagedSystemInterface>();
	
	//Native Methods
	private static native String[] nativeInterfaceGetAllInterfaceNames();
	private static native String[] nativeInterfaceGetAllWiFiInterfaceNames();
	private native boolean nativeInterfaceExists(String interfaceName);
	private native boolean nativeInterfaceIsWiFi(String interfaceName);
	private native String nativeInterfaceGetSSID(String interfaceName);
	private native String nativeInterfaceGetNickname(String interfaceName);
	private native String nativeInterfaceGetHardwareAddress(String interfaceName);
	private native float nativeInterfaceGetFrequency(String interfaceName);
	private native int nativeInterfaceGetBitRate(String interfaceName);
	private native boolean nativeInterfaceIsCableConnected(String interfaceName);
	
	/**
	 * Instantiates a new system interface using the given interface name.
	 * This object will always be instantiated, even if the given interface name
	 * does not exist. You may call the {@link exists} method to determine if the interface
	 * exists on the system.
	 *
	 * @param interfaceName the interface name, ex: eth0, wlan0, ra0, etc
	 */
	public SystemInterface(String interfaceName) {
		interfaceName_ = interfaceName;
	}
	
	/**
	 * Returns a ManagedSystemInterface. Only one ManagedSystemInterface object exists
	 * per SystemInterface
	 *
	 * @return the managed system interface
	 * @throws NonexistantSystemInterface the nonexistant system interface
	 */
	public synchronized ManagedSystemInterface manageSystemInterface() throws NonexistantSystemInterface {
		if(!exists()) {
			throw new NonexistantSystemInterface();
		}
		if(!managedSystemInterfaces.containsKey(interfaceName_)) {
			ManagedSystemInterface mObject = new ManagedSystemInterface(interfaceName_);
			managedSystemInterfaces.put(interfaceName_, mObject);
			return mObject;
		} else {
			return managedSystemInterfaces.get(interfaceName_);
		}
	}
	
	/**
	 * Gets the names of all interfaces known to the system.
	 *
	 * @return String[] of all interface names
	 */
	public static String[] getAllInterfaceNames() {
		return nativeInterfaceGetAllInterfaceNames();
	}
	
	/**
	 * Gets the names all WiFi interfaces known to the system.
	 *
	 * @return String[] of all WiFi interface names
	 */
	/*TODO: Sometimes interfaces do not show in /proc/dev/wireless unless they are
	 * connected. This a problem that needs to be handled.
	 */
	public static String[] getAllWiFiInterfaceNames() {
		return nativeInterfaceGetAllWiFiInterfaceNames();
	}
	
	@Override
	public String toString() {
		return interfaceName_;
	}
	
	/**
	 * Checks if the network interface represented by this SystemInterface object exists locally
	 * on the system.
	 *
	 * @return true, if the network interface exists.
	 */
	public boolean exists() {
		return nativeInterfaceExists(interfaceName_);
	}
	
	/**
	 * Checks if the network interface represented by this SystemInterface object is WiFi interface
	 *
	 * @return true, if WiFi
	 */
	public boolean isWiFi() {
		return nativeInterfaceIsWiFi(interfaceName_);
	}
	
	/**
	 * Gets the SSID of the currently connected WiFi network
	 *
	 * @return the SSID as a String
	 * @throws NonexistantSystemInterface if the network interface does not exist
	 * @throws InvalidSystemInterface if the network interface is not compatible with this method
	 */
	public String getSSID() throws NonexistantSystemInterface, InvalidSystemInterface {
		if(!exists()) {
			throw new NonexistantSystemInterface();
		}
		if(!isWiFi()) {
			throw new InvalidSystemInterface();
		}
		return nativeInterfaceGetSSID(interfaceName_);
	}
	
	/**
	 * Gets the nickname associated with the WiFi network interface
	 *
	 * @return the nickname
	 * @throws NonexistantSystemInterface if the network interface does not exist
	 * @throws InvalidSystemInterface if the network interface is not compatible with this method
	 */
	public String getNickname() throws NonexistantSystemInterface, InvalidSystemInterface {
		if(!exists()) {
			throw new NonexistantSystemInterface();
		}
		if(!isWiFi()) {
			throw new InvalidSystemInterface();
		}
		return nativeInterfaceGetNickname(interfaceName_);
	}
	
	/**
	 * Gets the hardware address (MAC Address) in the format of:
	 * xx:xx:xx:xx:xx:xx
	 *
	 * @return the hardware address as a String
	 * @throws NonexistantSystemInterface the network interface does not exist 
	 */
	public String getHardwareAddress() throws NonexistantSystemInterface {
		if(!exists()) {
			throw new NonexistantSystemInterface();
		}
		return nativeInterfaceGetHardwareAddress(interfaceName_);
	}
	
	/**
	 * Gets the frequency the WiFi is operating on in Hz
	 *
	 * @return the frequency in hertz
	 * @throws NonexistantSystemInterface if the network interface does not exist
	 * @throws InvalidSystemInterface if the network interface is not compatible with this method
	 */
	public float getFrequency() throws NonexistantSystemInterface, InvalidSystemInterface {
		if(!exists()) {
			throw new NonexistantSystemInterface();
		}
		if(!isWiFi()) {
			throw new InvalidSystemInterface();
		}
		return nativeInterfaceGetFrequency(interfaceName_);
	}
	
	/**
	 * Gets the current bit rate of the WiFi connection in bits per second
	 *
	 * @return the bit rate in bits per second
	 * @throws NonexistantSystemInterface if the network interface does not exist
	 * @throws InvalidSystemInterface if the network interface is not compatible with this method
	 */
	public int getBitRate() throws NonexistantSystemInterface, InvalidSystemInterface {
		if(!exists()) {
			throw new NonexistantSystemInterface();
		}
		if(!isWiFi()) {
			throw new InvalidSystemInterface();
		}
		return nativeInterfaceGetBitRate(interfaceName_);
	}
	
	/**
	 * Checks if the cable is connected.
	 *
	 * @return true, if the cable is connected
	 * @throws NonexistantSystemInterface if the network interface does not exist
	 * @throws InvalidSystemInterface if the network interface is not compatible with this method
	 */
	public boolean isCableConnected() throws NonexistantSystemInterface, InvalidSystemInterface {
		if(!exists()) {
			throw new NonexistantSystemInterface();
		}
		if(isWiFi()) {
			throw new InvalidSystemInterface();
		}
		return nativeInterfaceIsCableConnected(interfaceName_);
	}
	
}
