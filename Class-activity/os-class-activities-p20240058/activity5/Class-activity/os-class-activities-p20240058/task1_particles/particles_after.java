package task1_particles;

import java.util.concurrent.Semaphore;

public class particles_after {
    private static final int BUFFER_CAPACITY = 100; 
    private static final String[] buffer = new String[BUFFER_CAPACITY];
    private static int head = 0;
    private static int tail = 0;
    private static int count = 0;

    private static int producedPairs = 0;
    private static int packagedPairs = 0;

    // Semaphores setup
    private static final Semaphore empty_pairs = new Semaphore(50); // Tracks room for pairs (50 pairs max)
    private static final Semaphore full_pairs = new Semaphore(0);   // Tracks available pairs ready for intake
    private static final Semaphore mutex = new Semaphore(1);        // Protects critical pointers

    static class Producer implements Runnable {
        private final int machineId;
        private int pairId = 0;

        public Producer(int id) {
            this.machineId = id;
        }

        @Override
        public void run() {
            try {
                while (true) {
                    String p1 = "M" + machineId + "-" + pairId + "-P1";
                    String p2 = "M" + machineId + "-" + pairId + "-P2";

                    empty_pairs.acquire(); // Check for space (blocks if buffer is full)
                    mutex.acquire();       // Enter critical section

                    if (count + 2 > BUFFER_CAPACITY) {
                        System.out.println("The producing machine is broken");
                        System.exit(1);
                    }

                    buffer[tail] = p1;
                    tail = (tail + 1) % BUFFER_CAPACITY;
                    count++;

                    buffer[tail] = p2;
                    tail = (tail + 1) % BUFFER_CAPACITY;
                    count++;

                    producedPairs++;
                    pairId++;

                    mutex.release();       // Exit critical section
                    full_pairs.release();  // Inform consumer that a pair is complete

                    Thread.sleep(40); 
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    static class Consumer implements Runnable {
        @Override
        public void run() {
            try {
                while (true) {
                    full_pairs.acquire(); // Check for available pairs (blocks if buffer empty)
                    mutex.acquire();      // Enter critical section

                    if (count < 2) {
                        System.out.println("The packaging machine is broken");
                        System.exit(1);
                    }

                    String p1 = buffer[head];
                    buffer[head] = null;
                    head = (head + 1) % BUFFER_CAPACITY;
                    count--;

                    String p2 = buffer[head];
                    buffer[head] = null;
                    head = (head + 1) % BUFFER_CAPACITY;
                    count--;

                    String[] parts1 = p1.split("-");
                    String[] parts2 = p2.split("-");

                    if (!parts1[0].equals(parts2[0]) || !parts1[1].equals(parts2[1])) {
                        System.out.println("Pairs are incorrect");
                        System.exit(1);
                    }

                    packagedPairs++;
                    System.out.println("Produced pairs: " + producedPairs + " | Packaged pairs: " + packagedPairs + " | Buffer count: " + count);

                    mutex.release();       // Exit critical section
                    empty_pairs.release(); // Free space for an empty pair slot

                    Thread.sleep(30);
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        System.out.println("--- Particle Pair Simulation After Semaphores ---");
        for (int i = 1; i <= 3; i++) {
            new Thread(new Producer(i)).start();
        }
        new Thread(new Consumer()).start();
    }
}
