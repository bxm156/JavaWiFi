package com.bryanmarty.javawifi;

import static org.junit.Assert.*;

import org.junit.Test;

public class SystemInterfaceTest {

	@Test
	public void test() {
		SystemInterface i1 = new SystemInterface("eth0");
		assertTrue(i1.exists());
		assertFalse(i1.isWiFi());
		SystemInterface i2 = new SystemInterface("lo");
		assertTrue(i2.exists());
		assertFalse(i2.isWiFi());
		SystemInterface i3 = new SystemInterface("bad");
		assertFalse(i3.exists());
		SystemInterface i4 = new SystemInterface("ra0");
		assertTrue(i4.exists());
		assertTrue(i4.isWiFi());
		
		
	}

}
