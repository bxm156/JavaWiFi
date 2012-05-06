package com.bryanmarty.javawifi;

import static org.junit.Assert.*;

import org.junit.Test;

import com.bryanmarty.javawifi.exceptions.InvalidSystemInterface;
import com.bryanmarty.javawifi.exceptions.NonexistantSystemInterface;

public class SystemInterfaceTest {

	@Test
	public void test() throws NonexistantSystemInterface, InvalidSystemInterface {
		SystemInterface i1 = new SystemInterface("eth0");
		assertTrue(i1.exists());
		assertFalse(i1.isWiFi());
		System.out.println("Cable:" + i1.isCableConnected());
		SystemInterface i2 = new SystemInterface("lo");
		assertTrue(i2.exists());
		assertFalse(i2.isWiFi());
		SystemInterface i3 = new SystemInterface("bad");
		assertFalse(i3.exists());
		SystemInterface i4 = new SystemInterface("ra0");
		assertTrue(i4.exists());
		assertTrue(i4.isWiFi());
		System.out.println(i4.getSSID());
		assertEquals("CaseGuest",i4.getSSID());
		assertEquals("f4:6d:04:b1:8e:b1",i4.getHardwareAddress());
		System.out.println("Freq:" + i4.getFrequency());
		assertEquals("RT2870STA",i4.getNickname());
		//assertEquals(54000000,i4.getBitRate());
		System.out.println("All Interfaces:");
		for(String s : SystemInterface.getAllInterfaceNames()) {
			System.out.println(s);
		}
		System.out.println("WiFi");
		for(String s : SystemInterface.getAllWiFiInterfaceNames()) {
			System.out.println(s);
		}
	}

}
