import java.nio.ByteBuffer;
import java.util.Scanner;
import fmcb.Register;
import fmcb.Memory;

public class Run {

    public static volatile boolean shouldExit = false;

    static {
        System.loadLibrary("libJavaWrapperDef"); // Loads C++ library to provide definitions for the API Java wrapper.
    }

    static class InputThread extends Thread {

        public void run() {
            Scanner scanner = new Scanner(System.in);
    
            scanner.nextLine();
    
            Run.shouldExit = true;
    
            scanner.close();
        }
    
    }

    public static void main(String[] args) {
        InputThread input = new InputThread();
        input.start();

        System.out.println("Attempting to connect to core server");

        // ! Isn't used by request() yet
        // registration::initialize("JavaTest");

        if (Register.request() == 0) {
            System.out.println("Connection successful");

            ByteBuffer buffer = Memory.mapBuffer();

            System.out.println(buffer);

            buffer.put(0, (byte) 5);

            while (!shouldExit) {
                if (buffer.get(512) == 5) {
                    break;
                }

                try {
                    Thread.sleep(250);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }

            System.out.println(Memory.unmapBuffer());
        } else {
            System.out.println("Connection failed");
        }

        System.out.println("Exiting");
    }
}