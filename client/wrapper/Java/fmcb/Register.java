package fmcb;

public class Register {

	/**
	 * Initializes the request system with the given name.
	 * 
	 * @return
	 * 	<code>true</code> if the function succeeded.<br>
	 * 	<code>false</code> if {@code name} is longer than the maximum allowed by the client api.
	 */
	public native static boolean initialize(String name);

	/**
	 * Attempts to connect to the core server and register the client.
	 * {@link #initialize()} must have been called prior. If not, behavior is undefined.
	 * 
	 * @return
	 * 	The received status code as a result of the registration.<br>
	 * 	-1 if the core server was busy.
	 */
	public native static byte request();

}