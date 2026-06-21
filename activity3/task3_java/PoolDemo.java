/* PoolDemo.java — Thread Pool execution management using ExecutorService */
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class PoolDemo {
    static class Task implements Runnable {
        private int taskId;

        Task(int id) {
            this.taskId = id;
        }

        @Override
        public void run() {
            System.out.printf("Task #%d active on thread allocation node: %s (ID: %d)%n",
                taskId, Thread.currentThread().getName(), Thread.currentThread().getId());
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.printf("Task #%d finished work processing step on thread: %s%n", taskId, Thread.currentThread().getName());
        }
    }

    public static void main(String[] args) throws InterruptedException {
        System.out.println("Main: Spawning a Fixed Thread Pool of size 2 to execute 6 total tasks\n");

        /* Create a thread pool limit configuration boundary of exactly 2 threads */
        ExecutorService pool = Executors.newFixedThreadPool(2);

        /* Submit 6 tasks to the thread pool execution queue */
        for (int i = 1; i <= 6; i++) {
            pool.submit(new Task(i));
        }

        /* Order system shutdown sequence (Stops accepting new inputs, finishes current queue items) */
        pool.shutdown();
        pool.awaitTermination(30, TimeUnit.SECONDS);

        System.out.println("\nMain thread context: All queued items completed. Pool destroyed.");
    }
}
