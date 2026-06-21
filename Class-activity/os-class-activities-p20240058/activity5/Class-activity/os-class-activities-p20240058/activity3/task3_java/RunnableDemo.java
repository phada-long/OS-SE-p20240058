/* RunnableDemo.java — Threading via Implementing Runnable Interface */
public class RunnableDemo {
    static class PrintTask implements Runnable {
        private String taskName;

        PrintTask(String name) {
            this.taskName = name;
        }

        @Override
        public void run() {
            for (int i = 1; i <= 3; i++) {
                System.out.printf("[%s] Task Step %d (Thread Driver Name: %s, Thread ID: %d)%n",
                    taskName, i, Thread.currentThread().getName(), Thread.currentThread().getId());
                try {
                    Thread.sleep(300);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        System.out.println("Main: Spawning concurrent execution tasks using Runnable Interfaces\n");

        /* Package runnable items inside standard core Thread execution drivers */
        Thread t1 = new Thread(new PrintTask("Download"), "downloader");
        Thread t2 = new Thread(new PrintTask("Process"), "processor");
        Thread t3 = new Thread(new PrintTask("Upload"), "uploader");

        t1.start();
        t2.start();
        t3.start();

        t1.join();
        t2.join();
        t3.join();

        System.out.println("\nMain thread: Sequential runtime streams complete.");
    }
}
