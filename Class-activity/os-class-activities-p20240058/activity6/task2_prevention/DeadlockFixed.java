import java.util.concurrent.Semaphore;

class Account {
    String name;
    int balance;
    Account(String name, int balance) {
        this.name = name;
        this.balance = balance;
    }
}

public class DeadlockFixed {
    // The "Gatekeeper" that prevents deadlock
    static Semaphore mutex = new Semaphore(1);
    
    static void transfer(Account from, Account to, int amount) {
        try {
            // Acquire the mutex before doing anything
            mutex.acquire();
            System.out.println(Thread.currentThread().getName() + " acquired mutex, starting transfer");
            
            Thread.sleep(100); // Simulate processing time

            from.balance -= amount;
            to.balance += amount;
            
            System.out.println(Thread.currentThread().getName() + " transferred " + amount + " from " + from.name + " to " + to.name);
            
            // Release the mutex after transfer
            mutex.release();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        Account a = new Account("Account-A", 1000);
        Account b = new Account("Account-B", 1000);

        Thread t1 = new Thread(() -> transfer(a, b, 100), "Worker-1");
        Thread t2 = new Thread(() -> transfer(b, a, 200), "Worker-2");

        t1.start();
        t2.start();
        
        // Simple join to wait for finish
        try { t1.join(); t2.join(); } catch (Exception e) { e.printStackTrace(); }
        
        System.out.println("Final A: " + a.balance);
        System.out.println("Final B: " + b.balance);
        System.out.println("No deadlock occurred");
    }
}
