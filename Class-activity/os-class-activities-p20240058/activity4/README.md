# Class Activity 4 — Shared File API Report

**Name:** Nhem Phada
**ID:**p20240058  
**Course:** Operating Systems (Y2-S2)  

---

## 📸 Experiment Deliverables & Screenshots

### 1. C++ Implementation Before Mutex
* **Observed Behavior:** When 20 simultaneous client requests were sent, multiple threads read the file state at the same value before a disk write back occurred. This interleaved execution caused a race condition, leading to data overwrites.
* **Final Unsynchronized Score:** 2 (Out of 20 expected)
* **Screenshot Link:** `![C++ Before Mutex](screenshots/cpp_before_mutex.png)`

### 2. C++ Implementation After Mutex
* **Observed Behavior:** Using `std::lock_guard<std::mutex>` locked the file operations into a critical section. Threads were forced to execute sequentially, which prevented interleaved read/write cycles.
* **Final Synchronized Score:** 20
* **Screenshot Link:** `![C++ After Mutex](screenshots/cpp_after_mutex.png)`

### 3. Java Implementation Before Synchronized
* **Observed Behavior:** Standard Java concurrent threads accessed the file handling logic simultaneously without monitor locks. Threads fell into the sleep delay together, causing lost updates.
* **Final Unsynchronized Score:** 2
* **Screenshot Link:** `![Java Before Synchronized](screenshots/java_before_synchronized.png)`

### 4. Java Implementation After Synchronized
* **Observed Behavior:** Declaring the method as `synchronized` forced threads to acquire the class-level monitor lock before execution. Threads processed the shared resource sequentially.
* **Final Synchronized Score:** 20
* **Screenshot Link:** `![Java After Synchronized](screenshots/java_after_synchronized.png)`

---

## 📝 Lab Conceptual Questions & Answers

### 1. Why does a race condition happen when multiple clients try to update `shared_score.txt` without synchronization?
A race condition happens because the file update process consists of three distinct steps: **Read** the current score from disk, **Modify** (increment) the value in memory, and **Write** the updated value back to disk. Without synchronization, multiple server threads execute these steps concurrently. Multiple threads read the same initial value from the file before any of them can write the incremented value back, causing them to write the exact same number and overwrite each other's work.

### 2. How does `std::mutex` in C++ prevent data corruption in the shared file?
`std::mutex` provides mutual exclusion by acting as a binary lock. When a thread uses `std::lock_guard`, it acquires the mutex lock before entering the file update code. If other threads attempt to access the same block of code, the operating system blocks them and forces them to wait in a queue until the holding thread releases the lock. This guarantees that only one thread can execute the Read-Modify-Write cycle at any given time.

### 3. What does the `synchronized` keyword do in Java to protect the critical section?
In Java, the `synchronized` keyword utilizes an implicit internal lock called a **monitor lock**. When a thread invokes a synchronized method, it automatically acquires the monitor lock for that object or class. Other threads attempting to execute any synchronized section on that monitor are forced into a blocked state until the active thread finishes the method and releases the lock.

### 4. What is a "Critical Section" in this activity? Identify the specific lines of code that make up the critical section.
A Critical Section is a shared block of code that accesses or modifies a shared resource that could cause data corruption if accessed concurrently by multiple execution paths. 
In this activity, the critical section corresponds to the file operations block inside the `updateScore` / `update_score` functions:
* **Opening and reading the file:** `input >> score;` / `reader.readLine();`
* **Modifying the data:** `score++;`
* **Writing and saving back to disk:** `output << score;` / `writer.write();`

### 5. Why is the final score expected to be 20 when Student A sends 10 requests and Student B sends 10 requests?
With proper mutual exclusion synchronization (using Mutex or Synchronized), every single client request is processed as an isolated, atomic transaction. Since 20 distinct requests are sent, and no updates overwrite each other, the counter will increment exactly 20 times sequentially, ensuring deterministic output correctness.

### 6. What could happen if two separate servers update the same file at the same time?
If two entirely separate server programs or processes try to update the same physical file on disk without an external operating-system-level distributed lock (like a file lock / `flock`), the internal synchronization primitives like `std::mutex` or `synchronized` will fail. This is because those locks only control threads within their own process. The two independent servers would interleave their disk write cycles, resulting in severe file system corruption or data loss.

---

## 💭 Reflection
This activity demonstrates that moving shared variables from volatile RAM memory down to persistent physical storage disk media does not protect them from race conditions. Centralizing file modification inside a single server API is a great structural design choice, but because the server utilizes multi-threading to handle high client concurrency, internal thread synchronization is still mandatory. 

C++'s `std::mutex` (via RAII `std::lock_guard`) and Java's block-level `synchronized` keyword provide equivalent safety guarantees. The core difference is that C++ handles synchronization explicitly through explicit lock objects managed by the developer, whereas Java encapsulates it elegantly directly into the runtime system using built-in method modifiers and monitor objects.
