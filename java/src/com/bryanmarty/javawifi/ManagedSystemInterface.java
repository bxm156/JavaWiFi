package com.bryanmarty.javawifi;

import com.bryanmarty.javawifi.exceptions.InvalidSystemInterface;

public class ManagedSystemInterface extends SystemInterface {
	
	
	
	public ManagedSystemInterface(String interfaceName) {
		super(interfaceName);
	}
	
	/**
	 * Disconnect the WiFi connection
	 *
	 * @return true, if successful
	 * @throws InvalidSystemInterface the invalid system interface
	 */
	public boolean disconnectWiFi() throws InvalidSystemInterface {
		if(!isWiFi()) {
			throw new InvalidSystemInterface();
		}
		return true;
	}
	
	/**
	 * Brings the network interface up
	 *
	 * @return true, if successful
	 */
	public boolean up() {
		return true;
	}
	
	/**
	 * Takes the network interface down
	 *
	 * @return true, if successful
	 */
	public boolean down() {
		return true;
	}

}
