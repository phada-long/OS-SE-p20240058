# commands.md — exact commands I ran, per part

> Paste the **real** commands you ran, in order, in the fenced blocks below. Graded for
> command competency and is your defence if any output is questioned. One block per part.
> Delete the hint comments and replace with your actual commands.

## Part A — Threads, Mapping & Signals

```bash
# compile the threaded program (mind the threading flag), run it
# capture the 1:1 user→kernel (LWP) mapping into thread_map.txt while it runs
# compile/run signal_demo and demonstrate catching the interactive interr
cd ~/os-se-p20240058/final-exam/partA_threads
nano thread_demo.c
gcc -pthread -o thread_demo thread_demo.c
./thread_demo
./thread_demo & PID=$!; sleep 0.5; ps -eLf | head -1 > thread_map.txt; ps -eLf | grep " $PID " >> thread_map.txt; wait
nano thread_demo.c
nano signal_demo.c
gcc -o signal_demo signal_demo.c
./signal_demo
```

## Part B — Permissions, Special Bits & ACLs

```bash
cd ~/os-se-p20240058/final-exam/partB_security
mkdir -p story/shared
touch story/private.txt
echo "QuantumTech confidential notes" > story/private.txt
chmod 600 story/private.txt
chmod 711 story/shared
ls -l story/private.txt > perm_report.txt
ls -ld story/shared >> perm_report.txt
stat story/private.txt >> perm_report.txt
mkdir -p story/teamdir
chmod 2775 story/teamdir
chmod +t story/teamdir
ls -ld story/teamdir
gcc -o setuid_demo setuid_demo.c
chmod u+s setuid_demo
ls -l setuid_demo
./setuid_demo
```

## Part C — Bash Scripting, PATH & Safe Scanning

```bash
cd ~/os-se-p20240058/final-exam/partC_scripting
chmod +x scripts/greeter
cp scripts/greeter ~/bin/greeter
export PATH=$HOME/bin:$PATH
echo 'export PATH=$HOME/bin:$PATH' >> ~/.bashrc
greeter
echo "PATH=$PATH" > path_report.txt
which greeter >> path_report.txt
mkdir -p sample_dirs/dir1 sample_dirs/dir2 sample_dirs/dir3
chmod +x scripts/collector
./scripts/collector
cat collector_report.txt
```

## Part D — Race Condition & flock

```bash
cd ~/os-se-p20240058/final-exam/partD_secure
chmod +x scripts/buy_beacon
echo "100" > stock.txt
./scripts/buy_beacon Alice 5
chmod +x scripts/swarm
echo "100" > stock.txt; ./scripts/swarm; echo "Run 1 final stock: $(cat stock.txt)" >> observations.txt
echo "100" > stock.txt; ./scripts/swarm; echo "Run 2 final stock: $(cat stock.txt)" >> observations.txt
echo "100" > stock.txt; ./scripts/swarm; echo "Run 3 final stock: $(cat stock.txt)" >> observations.txt
# patched buy_beacon adds: ( flock -x 200; ...critical section... ) 200>"$LOCK_FILE"
echo "100" > stock.txt
./scripts/swarm
echo "Patched final stock: $(cat stock.txt)" >> observations.txt
```

## Part E — Backups & cron

```bash
cd ~/os-se-p20240058/final-exam/partE_automation
mkdir -p sample_project/src sample_project/docs
chmod +x scripts/backup_project
for i in 1 2 3 4 5; do ./scripts/backup_project; sleep 1; done
ls -la project_backups/; cat project_backups/backup.log
chmod +x scripts/timed_job; cp scripts/timed_job ~/bin/timed_job
(crontab -l 2>/dev/null; echo "* * * * * $HOME/bin/timed_job $LOGDIR/cron_recurring.log") | crontab -
(crontab -l 2>/dev/null; echo "35 14 * * * $HOME/bin/timed_job $LOGDIR/cron_oneshot.log") | crontab -
chmod +x scripts/backup_exam; cp scripts/backup_exam ~/bin/backup_exam
./scripts/backup_exam
(crontab -l 2>/dev/null; echo "*/2 * * * * $HOME/bin/backup_exam") | crontab -
(crontab -l 2>/dev/null; echo "0 16 * * * $HOME/bin/backup_exam") | crontab -
crontab -l
cat logs/cron_recurring.log
ls ~/exam-backups/
```
