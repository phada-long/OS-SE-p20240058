package task2_hello;

import java.util.concurrent.Semaphore;

public class hello_after {
    private static final Semaphore start_h = new Semaphore(1); // Permits immediate start
    private static final Semaphore after_e = new Semaphore(0); // Blocked initially
    private static final Semaphore after_l1 = new Semaphore(0); // Blocked initially
    private static final Semaphore after_l2 = new Semaphore(0); // Blocked initially

    public static void main(String[] args) throws InterruptedException {
        System.out.print("Output after semaphore ordering: ");

        Thread process1 = new Thread(() -> {
            try {
                start_h.acquire();
                System.out.print("H");
                System.out.print("E");
                after_e.release(); // Trigger process 2
            } catch (InterruptedException e) {}
        });

        Thread process2 = new Thread(() -> {
            try {
                after_e.acquire(); // Wait for HE
                System.out.print("L");
                after_l1.release(); 
                
                after_l1.acquire();
                System.out.print("L");
                after_l2.release(); // Trigger process 3
            } catch (InterruptedException e) {}
        });

        Thread process3 = new Thread(() -> {
            try {
                after_l2.acquire(); // Wait for HELL
                System.out.print("O");
            } catch (InterruptedException e) {}
        });

        process1.start();
        process2.start();
        process3.start();

        process1.join();
        process2.join();
        process3.join();
        System.out.println();
    }
}
