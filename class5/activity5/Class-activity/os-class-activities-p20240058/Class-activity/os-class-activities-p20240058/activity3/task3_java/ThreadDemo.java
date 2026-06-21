/* ThreadDemo.java — Threading via Subclassing Thread Class */
public class ThreadDemo {
    static class CounterThread extends Thread {
        private String name;
        private int count;

        CounterThread(String name, int count) {
            this.name = name;
            this.count = count;
        }

        @Override
        public void run() {
            for (int i = 1; i <= count; i++) {
                System.out.printf("[%s] Count iteration: %d (Internal Thread ID: %d)%n", name, i, Thread.currentThread().getId());
                try {
                    /* Pause execution for 500 milliseconds to observe interleaving */
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            System.out.printf("[%s] finished execution.%n", name);
        }
    }

    public static void main(String[] args) throws InterruptedException {
        System.out.println("Main engine thread (ID: " + Thread.currentThread().getId() + ") active...");
        System.out.println("Runtime Process ID PID: " + ProcessHandle.current().pid() + "\n");

        /* Instantiate 3 separate independent worker tasks */
        CounterThread t1 = new CounterThread("Alpha", 5);
        CounterThread t2 = new CounterThread("Beta", 5);
        CounterThread t3 = new CounterThread("Gamma", 5);

        /* Start execution loops concurrently */
        t1.start();
        t2.start();
        t3.start();

        /* Parent main thread blocks until worker execution tasks finish */
        t1.join();
        t2.join();
        t3.join();

        System.out.println("\nMain thread context: All target tasks finished.");
    }
}
