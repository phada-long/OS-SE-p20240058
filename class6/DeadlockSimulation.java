// Simple Watchdog Example
new Thread(() -> {
    try {
        Thread.sleep(2000); // Wait 2 seconds
        if (t1.isAlive() && t2.isAlive()) {
            System.out.println("Deadlock detected: transactions are stuck");
            System.out.println("Thread-1 is waiting for Account-2");
            System.out.println("Thread-2 is waiting for Account-1");
            System.exit(1);
        }
    } catch (InterruptedException e) { e.printStackTrace(); }
}).start();
