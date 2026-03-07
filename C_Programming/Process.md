Unix Process States, Fork, Zombie Processes, and Child Reaping
1. Overview

In Unix-like operating systems, processes transition through several states during their lifecycle. Understanding these states is essential for system programming, server design, and debugging process-related issues.

This document covers:

Process states

Process creation with fork()

Zombie processes

How zombies are handled

wait() vs waitpid()

Handling multiple children

Non-blocking reaping

Server-style process management (prefork model)

2. Process States in Unix/Linux

Processes move between several kernel states during execution.

State	Description
Running	Process is executing or ready to run
Interruptible Sleep	Waiting for an event, signals can wake it
Uninterruptible Sleep	Waiting for kernel I/O, signals ignored
Stopped	Suspended via signal (e.g., debugger)
Zombie	Process exited but parent hasn't collected status
Dead	Process fully removed from process table
2.1 Running State

The process is either:

currently executing on CPU

ready to run

TASK_RUNNING

Scheduler decides which process runs.

2.2 Interruptible Sleep

Process waits for an event and can be awakened by signals.

Examples:

waiting for user input

waiting on pipe/socket

sleeping (sleep())

Process state:

TASK_INTERRUPTIBLE

Signals can wake the process.

2.3 Uninterruptible Sleep

Process is waiting for kernel resources or hardware I/O.

TASK_UNINTERRUPTIBLE

Common causes:

disk I/O

NFS filesystem

device driver operations

memory paging

In tools like ps or top, this appears as:

D state (disk sleep)

Signals such as kill -9 will not terminate the process immediately while in this state.

2.4 Stopped State

Process execution is paused.

Examples:

debugger breakpoints

job control (Ctrl+Z)

TASK_STOPPED
2.5 Zombie State

Occurs when:

process exits

parent has not yet collected exit status

TASK_ZOMBIE

Zombie processes:

consume no CPU

consume no memory

only occupy process table entry

3. Process Creation with fork()

Processes create children using:

pid_t fork();

Behavior:

Return Value	Meaning
0	Child process
>0	Parent receives child PID
-1	Fork failed

Example:

#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if(pid == 0)
    {
        printf("Child process\n");
    }
    else
    {
        printf("Parent process\n");
    }
}
Process Tree Example
Parent
   |
   |--- Child1
   |--- Child2
   |--- Child3

Each child is an independent process.

4. Process Termination

A process terminates by:

exit()
return from main()
signal termination

When a child exits:

Kernel frees memory

Kernel closes files

Kernel stores exit status

Process enters zombie state

Parent receives SIGCHLD signal

5. Zombie Processes
When does a process become zombie?

When:

child exits
parent has not called wait()

Lifecycle:

fork()
   ↓
child running
   ↓
child exit()
   ↓
zombie
   ↓
parent wait()
   ↓
process removed
Why zombies exist

Kernel keeps zombie so parent can retrieve:

exit status

termination signal

resource usage

Example:

exit(5);

Parent retrieves status via:

wait(&status);
6. Problems if Zombies Accumulate

If parent never calls wait():

zombie entries remain

process table fills

system may reach PID limits

Possible error:

fork: Resource temporarily unavailable
7. How Zombies Are Handled
Case 1: Parent calls wait()

Normal cleanup.

child exits
   ↓
zombie created
   ↓
parent calls wait()
   ↓
zombie removed
Case 2: Parent dies

Child becomes orphan.

Adopted by PID 1 (init or systemd).

That process automatically calls wait().

8. wait() System Call

Prototype:

pid_t wait(int *status);

Behavior:

blocks until any child exits

returns PID of terminated child

Example:

int status;
pid_t pid = wait(&status);
Exit Status Macros
WIFEXITED(status)
WEXITSTATUS(status)
WIFSIGNALED(status)
WTERMSIG(status)

Example:

if (WIFEXITED(status))
{
    printf("exit code %d\n", WEXITSTATUS(status));
}
9. waitpid() System Call

Prototype:

pid_t waitpid(pid_t pid, int *status, int options);

More flexible than wait().

waitpid Parameters
pid parameter
Value	Meaning
>0	wait for specific child
-1	wait for any child
0	wait for same process group
< -1	wait for specific process group
status parameter

Pointer where exit status is stored.

Example:

int status;
options parameter
Option	Meaning
0	blocking
WNOHANG	non-blocking
WUNTRACED	report stopped child
WCONTINUED	report resumed child
10. Blocking vs Non-blocking
wait()

Always blocking.

Equivalent to:

waitpid(-1, &status, 0);
Non-blocking waitpid()
waitpid(-1, &status, WNOHANG);

Return values:

Return	Meaning
>0	child exited
0	no child exited
-1	error
11. Handling Multiple Children

One wait() call reaps only one child.

Example:

Parent has 3 zombie children.

Child1 Z
Child2 Z
Child3 Z

Calling wait() once:

Child1 removed
Child2 Z
Child3 Z

Parent must call wait again.

Correct Pattern
while(wait(NULL) > 0);

or

while(waitpid(-1,NULL,0) > 0);
12. Non-blocking Child Reaping

Used in servers.

while(waitpid(-1,NULL,WNOHANG) > 0)
{
}

Removes all zombies without blocking.

13. Using SIGCHLD

Kernel sends signal when child exits.

Signal handler example:

void handler(int sig)
{
    while(waitpid(-1,NULL,WNOHANG) > 0);
}

Register handler:

signal(SIGCHLD, handler);
14. Prefork Server Model

Used in many servers.

Architecture:

Master Process
   |
   |--- Worker1
   |--- Worker2
   |--- Worker3
   |--- Worker4

Master:

creates workers

monitors workers

respawns workers if needed

Workers:

handle client requests

15. Worker Lifecycle
master forks worker
      ↓
worker handles requests
      ↓
worker exits
      ↓
SIGCHLD sent to master
      ↓
master calls waitpid()
      ↓
master optionally spawns replacement
16. Example Prefork Server
Signal handler
void reap_workers(int sig)
{
    int status;
    pid_t pid;

    while((pid = waitpid(-1,&status,WNOHANG)) > 0)
    {
        printf("Worker %d exited\n", pid);
    }
}
Master process
int main()
{
    signal(SIGCHLD, reap_workers);

    for(int i=0;i<4;i++)
    {
        if(fork()==0)
        {
            worker_loop();
        }
    }

    while(1)
    {
        pause();
    }
}
Worker loop
void worker_loop()
{
    while(1)
    {
        accept_connection();
        handle_request();
    }
}
17. Production Server Pattern

Real servers avoid heavy work inside signal handlers.

Instead:

SIGCHLD received
      ↓
set flag
      ↓
main loop detects flag
      ↓
call waitpid()

Example:

while(1)
{
    if(child_exit_flag)
    {
        while(waitpid(-1,NULL,WNOHANG) > 0);
    }

    handle_events();
}
18. Key Takeaways

fork() creates child processes.

When child exits, it becomes a zombie until parent calls wait().

Zombies store exit status for the parent.

wait() blocks for any child.

waitpid() provides flexible control.

WNOHANG allows non-blocking child cleanup.

Each zombie requires one wait() call.

Servers use SIGCHLD + waitpid(WNOHANG) loops to clean zombies.

Prefork architectures manage worker processes dynamically.
