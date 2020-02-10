package main.java.side.server;

import java.nio.ByteBuffer;

public class MemoryUtils {

	static {
		System.loadLibrary("memAssist"); // Provides external C++ to provide definitions for this class.
	}

	public native static void createBuffer();

	public native static void closeBuffer();

	public native static ByteBuffer mapBuffer();

}
