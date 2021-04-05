package fmcb.util;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class NetworkUtils {

	//@SideOnly(Side.CLIENT)
	// public static void
	
	private Socket client;
	private DataOutputStream out;
	
	public NetworkUtils() {
		
	}

	public void createConnection() {
		try {
			System.out.println("Connecting to " + "73.229.57.119" + " on port " + 49200);
			client = new Socket("73.229.57.119", 49200);

			System.out.println("Just connected to " + client.getRemoteSocketAddress());
			OutputStream outToServer = client.getOutputStream();
			out = new DataOutputStream(outToServer);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void send(String msg) {
		try {
			out.writeUTF(msg + client.getLocalSocketAddress());
			InputStream inFromServer = client.getInputStream();
			DataInputStream in = new DataInputStream(inFromServer);

			System.out.println("Server says " + in.readUTF());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void closeConnection() {
		try {
			client.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
