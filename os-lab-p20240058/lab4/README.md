# Lab 4 — I/O Redirection, Pipelines & Process Management

| | |
|---|---|
| **Student Name** | Nhem Phada |
| **Student ID** | p20240058 |

## Task Completion

| Task | Output File | Status |
|------|-----------|--------|
| Task 1: I/O Redirection | `task1_redirection.txt` | ✅ |
| Task 2: Pipelines & Filters | `task2_pipelines.txt` | ✅ |
| Task 3: Data Analysis | `task3_analysis.txt` | ✅ |
| Task 4: Process Management | `task4_processes.txt` | ✅ |
| Task 5: Orphan & Zombie | `task5_orphan_zombie.txt` | ✅ |

## Screenshots

### Task 4 — top output
![top output](images/top_screenshot.png)

### Task 4 — htop tree view
![htop tree](images/htop_tree_screenshot.png)

### Task 4 — top highest memory process
![top memory](images/top_memory_screenshot.png)

### Task 5 — Orphan process (ps showing PPID = 1)
![orphan process](images/orphan_ps_output.png)

### Task 5 — Zombie process (ps showing state Z)
![zombie process](images/zombie_ps_output.png)

### Task 5 — Three children forest view
![three children](images/three_children_forest.png)

### Full terminal history
![history](images/history_screenshot.png)

## Answers to Task 5 Questions

1. **How are orphans cleaned up?**
   > When a parent exits before its child, the child is adopted by init (PID 1). Init calls wait() when the orphan eventually exits, cleaning it from the process table.

2. **How are zombies cleaned up?**
   > A zombie exists because the parent has not yet called wait() to collect the child's exit status. The zombie is removed when the parent calls wait(), or when the parent itself exits and init inherits the zombie and cleans it.

3. **Can you kill a zombie with kill -9? Why or why not?**
   > No. A zombie process is already dead — it has no executable code left to kill. It is just a process table entry holding the exit status. Only the parent calling wait() (or the parent dying) removes it.

## Reflection

> Pipelines and redirection are essential for server administration. Instead of scrolling through thousands of log lines manually, I can chain grep, awk, cut, and sort to extract exactly what I need in seconds. The ability to separate stdout from stderr and discard noise with /dev/null is critical when writing automation scripts. Understanding orphan and zombie processes also helps diagnose systems where runaway children accumulate and consume process table entries.
