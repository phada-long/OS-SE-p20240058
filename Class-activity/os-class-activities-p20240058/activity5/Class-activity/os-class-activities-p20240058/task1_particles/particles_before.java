package task1_particles;

import java.util.Random;

public class particles_before {
    private static final int BUFFER_CAPACITY = 100; 
    private static final String[] buffer = new String[BUFFER_CAPACITY];
    private static int head = 0;
    private static int tail = 0;
    private static int count = 0;

    private static int producedPairs = 0;
    private static int packagedPairs = 0;

    static class Producer implements Runnable {
        private final int machineId;
        private int pairId = 0;

        public Producer(int id) {
            this.machineId = id;
        }

        @Override
        public void run() {
            while (true) {
                String p1 = "M" + machineId + "-" + pairId + "-P1";
                String p2 = "M" + machineId + "-" + pairId + "-P2";

                // Dangerous unprotected validation check
                if (count + 2 > BUFFER_CAPACITY) {
                    System.out.println("The producing machine is broken");
                    System.exit(1);
                }

                // Add first particle unsafely
                buffer[tail] = p1;
                tail = (tail + 1) % BUFFER_CAPACITY;
                count++;

                // Artificially induce context switching to trigger race conditions
                try { Thread.sleep(new Random().nextInt(5)); } catch (InterruptedException e) {}

                // Add second particle unsafely
                buffer[tail] = p2;
                tail = (tail + 1) % BUFFER_CAPACITY;
                count++;

                producedPairs++;
                pairId++;

                try { Thread.sleep(15); } catch (InterruptedException e) {}
            }
        }
    }

    static class Consumer implements Runnable {
        @Override
        public void run() {
            while (true) {
                if (count < 2) {
                    System.out.println("The packaging machine is broken");
                    System.exit(1);
                }

                String p1 = buffer[head];
                head = (head + 1) % BUFFER_CAPACITY;
                count--;

                String p2 = buffer[head];
                head = (head + 1) % BUFFER_CAPACITY;
                count--;

                if (p1 == null || p2 == null) {
                    System.out.println("The packaging machine is broken");
                    System.exit(1);
                }

                // Split string array data to cross-examine matching signatures
                String[] parts1 = p1.split("-");
                String[] parts2 = p2.split("-");

                if (!parts1[0].equals(parts2[0]) || !parts1[1].equals(parts2[1])) {
                    System.out.println("Mismatched Pair Found: " + p1 + " paired with " + p2);
                    System.out.println("Pairs are incorrect");
                    System.exit(1);
                }

                packagedPairs++;
                System.out.println("Produced pairs: " + producedPairs + " | Packaged pairs: " + packagedPairs + " | Buffer count: " + count);

                try { Thread.sleep(20); } catch (InterruptedException e) {}
            }
        }
    }

    public static void main(String[] args) {
        System.out.println("--- Particle Pair Simulation Before Semaphores ---");
        for (int i = 1; i <= 3; i++) {
            new Thread(new Producer(i)).start();
        }
        new Thread(new Consumer()).start();
    }
}
