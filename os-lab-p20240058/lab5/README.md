# OS Lab 5 — Threads, Kernel Workers & Process Signals

**Student:** Nhem Phada (p20240058)
**Course:** Operating Systems
**Environment:** Ubuntu 24.04 (WSL2) on Windows

---

## Task 1 — Processes vs. Threads

Compared memory sharing behavior between `fork()` and `pthread_create()`.

- `process_test.c`: The child process modified `global_var` to 30, but the parent's copy remained 10 — confirming that processes do **not** share memory space (each gets its own copy via copy-on-write).
- `thread_test.c`: The spawned thread modified `global_var` to 30, and the main thread also saw 30 — confirming that threads **do** share the same memory space within a process.

Screenshots: `images/process_vs_thread_1.png`, `images/process_vs_thread_2.png`

---

## Task 2 — Thread Interaction

`multi_thread.c` created 3 worker threads using `pthread_create()`, each computing a result (`tid * 100`) and returning it via `pthread_exit()`. The main thread used `pthread_join()` to wait for and collect each thread's return status.

Observation: thread creation and completion order can interleave slightly differently between runs since the OS scheduler decides thread execution order — this is expected, normal multithreaded behavior.

Screenshot: `images/thread_interaction.png`

---

## Task 3 — Visualizing Kernel & User Threads

`sleeper_threads.c` spawned 2 threads that each sleep for 60 seconds, allowing time to inspect the process/thread mapping.

- `ps -eLf | grep $MAIN_PID` showed 3 rows for the same PID (main thread + 2 spawned threads), each with a distinct LWP (Lightweight Process / kernel thread ID) — demonstrating Linux's 1:1 threading model, where every user-level thread maps directly to one kernel-level thread.

Screenshot: `images/user_kernel_mapping.png`

**Note on kernel worker threads (htop):** This lab was completed in a WSL2 (Windows Subsystem for Linux) environment. WSL2 runs a minimal, virtualized Linux kernel that does **not** spawn or expose traditional kernel worker threads (e.g., `kworker`, `ksoftirqd`, `migration`) to userspace tools. This was verified directly:
ps -ef | grep '['      → no kernel-thread-style entries found
ps -ef | grep kworker   → no kworker processes found
htop (Tasks: X, Y thr, 0 kthr) → consistently reports 0 kernel threads
This is a known limitation of WSL2's lightweight kernel design, not an error in setup or configuration (both "Hide kernel threads" and "Show custom thread names" were correctly configured in htop's Display options). As the closest available demonstration of thread visualization in htop, the screenshot below shows htop's user-thread view (`H` toggle) of the `sleeper_threads` process, correctly displaying 3 rows — one for the main thread and one for each of the 2 spawned threads, sharing the same command name but distinct PIDs.

Screenshot: `images/htop_kernel_threads.png`

Attempted `kill -STOP <PID>` on a thread — on a native Linux system, attempting this on a true kernel thread would be blocked/restricted since kernel threads run in kernel space and are vital for system stability; this could not be fully demonstrated in WSL2 due to the kernel-thread visibility limitation above.

---

## Task 4 — Process Signals and Handling

`signal_handler.c` registered handlers for `SIGINT` and `SIGTERM` using `signal()`.

- **SIGINT (Ctrl+C):** Caught successfully — the handler printed a graceful shutdown message, simulated a 1-second cleanup delay, then exited safely.
- **SIGTERM (`kill -SIGTERM`):** Caught successfully — the handler printed a "Saving state..." message and exited.
- **SIGKILL (`kill -9`):** After adding an attempt to register a handler for `SIGKILL`, the program printed a warning ("Warning: Cannot catch SIGKILL") at startup, confirming the OS refuses to let this signal be caught. When `kill -9` was sent, the process was terminated **instantly** with no cleanup message — confirmed via `jobs`, which showed `[1]+ Killed ./signal_handler`. This proves SIGKILL cannot be caught, blocked, or ignored by user code.

Screenshot: `images/signal_sigint.png`

---

## Challenge — Multithreading with Signals

`challenge.c` combined threads and signal handling:
- Registered a `SIGINT` handler that sets a global flag `keep_running = 0`.
- Spawned 2 worker threads, each looping and printing their thread ID every second while `keep_running` is true.
- On `Ctrl+C`, the flag flips to 0, both threads detect this on their next loop check, print an exit message, and call `pthread_exit()`.
- The main thread joins both threads, then prints `"All threads cleanly exited. Goodbye."` before terminating.

This demonstrates safe, cooperative thread shutdown via a shared flag rather than forcibly killing threads.

Screenshot: `images/challenge_shutdown.png`

---

## Folder Structure
lab5/
├── README.md
├── thread_lab/
│   ├── process_test.c
│   ├── thread_test.c
│   ├── multi_thread.c
│   ├── sleeper_threads.c
│   ├── signal_handler.c
│   └── challenge.c
└── images/
├── process_vs_thread_1.png
├── process_vs_thread_2.png
├── thread_interaction.png
├── user_kernel_mapping.png
├── htop_kernel_threads.png
├── signal_sigint.png
└── challenge_shutdown.png

