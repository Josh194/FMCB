package main.java.util;

import java.nio.ByteBuffer;

public class MemoryUtils {

	static {
		System.loadLibrary("memAssist"); // Loads external C++ to provide definitions for this class.
	}

	/**
	 * Creates the IPC buffer in the system paging file, or opens it if already created.
	 * Call {@link #closeBuffer()} after all applications are finished with the buffer to prevent memory leaks.
	 * 
	 * @see #mapBuffer()
	 */
	public native static void createBuffer();

	/**
	 * Unmaps the IPC buffer from memory and cleans up any resources created by {@link #createBuffer()}.
	 * Failure to call this method will result in the buffer staying in memory until a restart or successful cleanup.
	 * <p>
	 * This method will complete regardless of the state of any other applications connected to the buffer,
	 * so calling it while they are still attempting to use the buffer may cause crashes.
	 */
	public native static void closeBuffer();
	// TODO Split closeBuffer() into separate unmap and close methods to allow applications to better communicate the buffer cleanup process.

	/**
	 * Maps the IPC buffer into the current process's memory, allowing it to access it like any other section of memory.
	 * 
	 * @return a <code>ByteBuffer</code> that can be used to access the IPC buffer.
	 */
	public native static ByteBuffer mapBuffer();

}
