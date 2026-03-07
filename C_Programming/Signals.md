# Unix Signal Handling Across Process States

## 1. Overview

Signals are a mechanism used by Unix kernels to **notify processes of events** such as:

- termination requests
- child process exit
- timer expiration
- illegal operations
- external interrupts

Signals may:

- terminate a process
- stop a process
- resume a process
- invoke a signal handler

However, **signal behavior depends on the current process state**.

---

# 2. Signal Handling Basics

When a signal is delivered to a process, the kernel checks the signal disposition:

Possible actions:

| Action | Meaning |
|------|--------|
| Default action | Kernel performs predefined behavior |
| Ignore | Signal discarded |
| Catch | User-defined signal handler executed |

Example handler:

```c
void handler(int sig)
{
    printf("Signal received\n");
}

signal(SIGINT, handler);
```

---

# 3. Signal Delivery Model

Signals are **asynchronous events**.

Signal delivery flow:

```
signal generated
      ↓
kernel marks signal pending
      ↓
process scheduled
      ↓
signal delivered
      ↓
handler executed or default action taken
```

Signals are typically delivered **when the process returns to user mode**.

---

# 4. Signals in Running State

Process state:

```
TASK_RUNNING
```

Behavior:

- signal is delivered immediately
- handler executes before the process continues

Example:

```
process running
     ↓
SIGINT received
     ↓
handler executed
     ↓
process resumes
```

---

# 5. Signals in Interruptible Sleep

Kernel state:

```
TASK_INTERRUPTIBLE
```

Behavior:

- signal **wakes the process**
- system call may return with error

Typical result:

```
EINTR (Interrupted system call)
```

Example:

```
process waiting on read()
       ↓
SIGINT received
       ↓
read() interrupted
       ↓
signal handler executed
```

This is common with:

- `read()`
- `select()`
- `poll()`
- `sleep()`

---

# 6. Signals in Uninterruptible Sleep

Kernel state:

```
TASK_UNINTERRUPTIBLE
```

Behavior:

- signals are **not processed immediately**
- signal becomes **pending**
- handled only after process leaves this state

Example situation:

```
process waiting for disk I/O
       ↓
SIGKILL sent
       ↓
process remains in D state
       ↓
I/O completes
       ↓
signal processed
```

Important property:

Even `SIGKILL` **cannot terminate immediately** in this state.

---

# 7. Signals in Stopped State

Kernel state:

```
TASK_STOPPED
```

Process is paused (e.g., `SIGSTOP`, `Ctrl+Z`).

Behavior depends on signal type.

| Signal | Effect |
|------|--------|
| SIGCONT | resumes process |
| SIGKILL | terminates immediately |
| other signals | delivered after resume |

Example:

```
process stopped
     ↓
SIGCONT
     ↓
process resumes execution
```

---

# 8. Signals in Zombie State

Kernel state:

```
TASK_ZOMBIE
```

Behavior:

- zombie processes **do not execute**
- signals **have no effect**

Reason:

The process has already exited and is waiting for parent cleanup.

Only action possible:

```
parent calls wait()
```

Then the kernel removes the process entry.

---

# 9. Signals During System Calls

Signals may interrupt blocking system calls.

Example:

```
read()
select()
poll()
nanosleep()
```

Behavior:

```
system call started
     ↓
signal delivered
     ↓
system call interrupted
     ↓
returns -1 with errno = EINTR
```

Programs must handle this.

Example:

```c
while(read(fd, buf, n) == -1 && errno == EINTR)
{
    continue;
}
```

---

# 10. Pending Signals

If a process cannot immediately handle a signal, it becomes **pending**.

Examples:

- process in kernel mode
- uninterruptible sleep
- signal masked

Flow:

```
signal sent
     ↓
marked pending
     ↓
delivered when process resumes
```

---

# 11. Signal Masking

Processes can temporarily **block signals**.

Blocked signals become **pending**.

Example:

```c
sigset_t set;

sigemptyset(&set);
sigaddset(&set, SIGINT);

sigprocmask(SIG_BLOCK, &set, NULL);
```

Signals remain pending until unblocked.

---

# 12. Uncatchable Signals

Some signals cannot be handled or ignored.

| Signal | Purpose |
|------|---------|
| SIGKILL | force termination |
| SIGSTOP | force stop |

These are always handled by the kernel.

Example:

```
kill -9 <pid>
```

---

# 13. Signal Generation Sources

Signals may originate from:

| Source | Example |
|------|---------|
| user commands | kill |
| keyboard | Ctrl+C |
| kernel events | SIGSEGV |
| timers | SIGALRM |
| child exit | SIGCHLD |
| hardware faults | SIGFPE |

---

# 14. Signal Lifecycle Summary

```
signal generated
      ↓
kernel marks signal pending
      ↓
process scheduled
      ↓
signal delivered
      ↓
handler runs or default action executed
```

Delivery timing depends on **process state**.

---

# 15. Signal Behavior Summary by Process State

| Process State | Signal Behavior |
|---------------|----------------|
| Running | handled immediately |
| Interruptible Sleep | wakes process, system call interrupted |
| Uninterruptible Sleep | signal pending until I/O completes |
| Stopped | handled after resume or by SIGCONT |
| Zombie | ignored |

---

# 16. Key Takeaways

- Signals are **asynchronous notifications** delivered by the kernel.
- Behavior depends on the **current process state**.
- Signals interrupt **interruptible sleep**, but not **uninterruptible sleep**.
- Signals may cause system calls to return **EINTR**.
- Some signals (**SIGKILL**, **SIGSTOP**) cannot be caught or ignored.
- Zombies cannot receive or process signals.


# Additional Note — Signals Sent Between Processes

## 1. Process-to-Process Signals

In Unix, **one process can send signals to another process**.

This is commonly used for:

- process control
- inter-process communication (IPC)
- stopping or terminating programs
- notifying events

Signals are sent using system calls such as:

```
kill()
raise()
sigqueue()
```

---

# 2. kill() System Call

Prototype:

```c
int kill(pid_t pid, int sig);
```

Parameters:

| Parameter | Meaning |
|----------|--------|
| pid | target process or group |
| sig | signal number |

Example:

```c
kill(1234, SIGTERM);
```

This sends **SIGTERM** to process **PID 1234**.

---

# 3. kill() PID Semantics

The `pid` argument controls **who receives the signal**.

| pid value | Meaning |
|----------|--------|
| > 0 | send signal to specific process |
| 0 | send signal to all processes in same process group |
| -1 | send signal to all processes the caller has permission to signal |
| < -1 | send signal to process group |

Example:

```c
kill(-1234, SIGTERM);
```

Send signal to **process group 1234**.

---

# 4. raise() System Call

A process can send a signal **to itself**.

Prototype:

```c
int raise(int sig);
```

Example:

```c
raise(SIGINT);
```

Equivalent to:

```
kill(getpid(), SIGINT)
```

---

# 5. sigqueue() System Call

Allows sending a signal **with additional data**.

Prototype:

```c
int sigqueue(pid_t pid, int sig, union sigval value);
```

Example:

```c
union sigval val;
val.sival_int = 42;

sigqueue(pid, SIGUSR1, val);
```

The receiving process can read this data in the signal handler.

---

# 6. Permissions for Sending Signals

A process can send signals only if:

- it has the **same UID as the target process**
- or it has **superuser privileges (root)**

This prevents unauthorized control of other processes.

---

# 7. Common Example — Shell Terminating a Process

When you run:

```
kill -9 1234
```

What happens:

```
shell process
      ↓
kill() system call
      ↓
kernel sends SIGKILL
      ↓
target process terminated
```

---

# 8. Summary

Signals may originate from:

| Source | Example |
|------|---------|
| Kernel events | SIGSEGV, SIGFPE |
| Hardware interrupts | SIGINT |
| Timers | SIGALRM |
| Child process exit | SIGCHLD |
| **Other processes** | kill(), sigqueue() |

Process-to-process signaling is a **core Unix IPC and control mechanism**.
