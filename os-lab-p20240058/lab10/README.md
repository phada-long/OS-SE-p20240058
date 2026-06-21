# OS Lab 10 - The QuantumTech Automation Pipeline
**Student ID:** p20240058  
**Name:** Nhem Phada  

---

## Lab Questions & Answers

### Q1: What is the technical difference between archiving and compression? Which commands handle which?
- **Archiving** is the process of gathering multiple distinct files and directories together into a single composite container file. This preserves file structures, permissions, and metadata but does not reduce the overall byte footprint. It is handled by the `tar` utility.
- **Compression** applies mathematical algorithms to a data stream to eliminate redundant byte patterns, actively shrinking the actual storage space required on disk. This is handled by the `gzip` utility.

### Q2: Why is the `.tar.gz` file significantly smaller than the project folder itself?
The `.tar.gz` archive is dramatically smaller because the sample text documentation files (`changelog.txt` and `notes.txt`) contained highly sequential, repetitive numeric character arrangements generated via the `seq 1 500` loop. The DEFLATE/LZW compression algorithm easily detects these predictable patterns and replaces them with tiny dictionary pointers.

### Q3: Why do crontab entries require absolute paths instead of shortcuts like `~/bin/my_script`?
The `cron` daemon initializes automated workflows within a non-interactive background shell environment that completely bypasses your personal user login configuration profiles (like `.bashrc` or `.bash_profile`). Because custom environment variables like `$PATH` are minimized and shell shortcuts like the tilde (`~`) are left uninitialized, full absolute paths must be written so the system engine can locate the exact files on disk.

### Q4: Why must the `%` symbol be escaped with a backslash in crontab strings? What does `>> logfile 2>&1` do?
- In crontab syntax, an unescaped `%` character functions as an explicit newline marker that halts the command sequence and pipes all subsequent text directly into the script's standard input. It must be escaped as `\%` to be treated as a literal character (like in date formatting).
- The syntax `>> logfile` continually redirects and appends standard output messages into your log file, while `2>&1` binds the standard error channel to that exact same stream destination, ensuring both runtime confirmations and errors are logged together.

### Q5: Explain how the file-pruning logic works in the backup script.
The script handles automatic retention by listing all matching timestamped backups ordered by chronological age, newest first, using `ls -1t`. This stream is piped into `tail -n +4`, which skips the first 3 newest files (the ones we want to save) and captures any older, overflowing backup paths. These excess files are then systematically removed using `rm -f` to enforce a strict storage cap.

### Q6: Give the exact crontab line used to run a job at 2:30 PM on June 22nd. Which fields were modified?
```cron
30 14 22 6 * /home/phada/bin/deadline_job >> /home/phada/os-lab-automation/logs/cron_deadline_job.log 2>&1
The custom fields configured were: Minute (30), Hour (14 for 2:30 PM), Day of Month (22), and Month (6). The Day of Week field remained a wildcard (*).

Q7: Why is it dangerous to run crontab -r to clean up practice entries? What should be done instead?
crontab -r completely wipes out your entire active crontab file without confirmation. Running it would accidentally delete your critical, time-sensitive GRADED session and deadline configurations. Instead, you should always use a selective pipeline filter like crontab -l | grep -E 'GRADED|...' | crontab - to safely remove practice entries while leaving core tasks untouched.

Q8: What is the benefit of a maintenance script that checks disk usage and rotates logs?
It ensures long-term operational sustainability and prevents silent system crashes. Automated log rotation prevents history logs from slowly growing until they consume 100% of the disk, while threshold tracking alerts administrators of resource shortages proactively before system performance is affected.

Q9: Describe your custom automation job from Level 7. What does it do and what is its schedule?
Purpose: It functions as an automated real-time performance monitor. It samples system runtime details and logs continuous, timestamped load average decimals to a central log file to track system strain over time.

Schedule: Triggers precisely every 2 minutes using the */2 * * * * interval parameters during the validation phase.

Embedded Evidence Screenshots
Level 0 - Automation Warm-Up
Level 1 - Archiving & Compression
Level 2 - File & Folder Backup Script
Level 3 - Cron Fundamentals
Level 4 - Timed Graded Session Job
Level 4 - Timed Graded Deadline Job
Level 5 - Scheduling the Backup
Level 6 - Maintenance Automation
Level 7 - Design Your Own Scheduled Job
Level 8 - Teardown and Reset
