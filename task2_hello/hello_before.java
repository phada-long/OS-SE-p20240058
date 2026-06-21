package task2_hello;

public class hello_before {
    public static void main(String[] args) {
        System.out.print("Output before semaphore ordering: ");

        Thread process1 = new Thread(() -> {
            System.out.print("H");
            System.out.print("E");
        });

        Thread process2 = new Thread(() -> {
            System.out.print("L");
            System.out.print("L");
        });

        Thread process3 = new Thread(() -> {
            System.out.print("O");
        });

        process1.start();
        process2.start();
        process3.start();

        try {
            process1.join();
            process2.join();
            process3.join();
        } catch (InterruptedException e) {}
        System.out.println();
    }
}
