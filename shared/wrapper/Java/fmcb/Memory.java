package fmcb;

import java.nio.ByteBuffer;

/**
 * Java library for subsystems to access the communication buffer.
 */
public class Memory {

	/**
	 * Maps the IPC buffer into the current process's memory space, allowing it to access it like any other section of memory.
	 * Call {@link #closeBuffer()} after finished with it to prevent memory leaks.
	 * <p>
	 * A successful call to {@link Register#initialize()} must have been made prior, or the function will fail.
	 * 
	 * @return A <code>ByteBuffer</code> that can be used to access the IPC buffer, <code>null</code> if the function failed.
	 */
	public native static ByteBuffer mapBuffer();
	
	/**
	 * Unmaps the IPC buffer from memory and cleans up any resources created by {@link #createBuffer()}.
	 * <p>
	 * Failure for this method to fully complete may result in the buffer staying in system memory until a restart,
	 * so try to insure it can complete.
	 * Note that running this method multiple times and getting a return value of both 1 and 2 is the same as a success.
	 * 
	 * @return
	 *	0: If the function completed successfully.<br>
	 *	1: If the function failed to unmap the buffer.<br>
	 *	2: If the function failed to close the mapping handle.<br>
	 *	3: If the function failed.
	 */
	public native static byte unmapBuffer();

}
