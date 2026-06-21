import java.util.concurrent.Semaphore;

class Account {
    String name;
    int balance;
    Semaphore lock = new Semaphore(1);

    Account(String name, int balance) {
        this.name = name;
        this.balance = balance;
    }
}

class Transfer {
    static void transfer(Account from, Account to, int amount) {
        try {
            System.out.println(Thread.currentThread().getName() + " trying to lock FROM " + from.name);
            from.lock.acquire();
            System.out.println(Thread.currentThread().getName() + " locked FROM " + from.name);

            Thread.sleep(100);

            System.out.println(Thread.currentThread().getName() + " trying to lock TO " + to.name);
            to.lock.acquire();
            System.out.println(Thread.currentThread().getName() + " locked TO " + to.name);

            from.balance -= amount;
            to.balance += amount;
            System.out.println(Thread.currentThread().getName() + " transfer completed");

            to.lock.release();
            from.lock.release();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

public class DeadlockSimulation {
    public static void main(String[] args) {
        Account account1 = new Account("Account-1", 1000);
        Account account2 = new Account("Account-2", 1000);

        Thread t1 = new Thread(() -> Transfer.transfer(account1, account2, 100), "Thread-1");
        Thread t2 = new Thread(() -> Transfer.transfer(account2, account1, 200), "Thread-2");

        // Watchdog Thread to detect the deadlock
        new Thread(() -> {
            try {
                Thread.sleep(2000);
                if (t1.isAlive() && t2.isAlive()) {
                    System.out.println("Deadlock detected: transactions are stuck");
                    System.out.println("Thread-1 is waiting for Account-2");
                    System.out.println("Thread-2 is waiting for Account-1");
                    System.exit(1);
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }).start();

        t1.start();
        t2.start();
    }
}
