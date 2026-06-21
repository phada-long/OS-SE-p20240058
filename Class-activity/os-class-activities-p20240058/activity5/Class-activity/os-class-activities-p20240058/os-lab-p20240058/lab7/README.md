# OS Lab 7 — Bash Scripting, Permissions & Automation

## Student
Name: phada

## Overview
This lab demonstrates Bash scripting, Linux permissions, SUID programs, and automation across user directories.

---

## Tasks Completed

### Task 1: Warmup Script
- Created executable Bash script
- Learned chmod +x and script execution

### Task 2: PATH Configuration
- Added ~/bin to PATH
- Executed scripts without ./ prefix

### Task 3: Doorstep Login Message
- Customized .bashrc
- Displayed system info and random quotes

### Task 4: Secure Mailbox
- Configured write-only inbox using chmod 733

### Task 5: Broadcaster
- Generated public secrets with timestamp

### Task 6: VIP Guestbook (SUID)
- Created C program
- Enabled SUID execution to append guestbook entries

### Task 7: Data Harvester
- Scanned /home directories
- Collected readable secrets

### Task 8: Mailman Bot
- Sent automated messages to classmates based on harvested data

---

## Key Concepts Learned
- Bash scripting
- File permissions (chmod)
- PATH environment variable
- SUID security behavior
- Cross-user file access
- Automation using loops and conditions

---

## Submission Structure
lab7/
├── README.md
├── task1_warmup.txt
├── task2_path.txt
├── task3_doorstep.txt
├── task4_inbox.txt
├── task5_broadcaster.txt
├── task6_guestbook.txt
├── task7_harvester.txt
├── task8_mailman.txt
├── harvest_report.txt
├── sign_book.c
├── images/
└── scripts/
