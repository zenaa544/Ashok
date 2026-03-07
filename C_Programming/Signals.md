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


# D State and Signal Masking in Unix/Linux

## 1. What is D State?

In tools like `ps` or `top`, the process state **D** means:

```
Uninterruptible Sleep
```

Kernel state:

```
TASK_UNINTERRUPTIBLE
```

This means the process is **waiting inside the kernel for an operation to complete** and **cannot be interrupted by signals**.

---

# 2. Why the Kernel Uses D State

Certain operations must **not be interrupted**, otherwise the system could enter an inconsistent state.

Examples include:

- disk I/O
- filesystem operations
- device driver operations
- memory paging
- NFS operations

Example flow:

```
process calls read()
      ↓
kernel starts disk I/O
      ↓
process sleeps in D state
      ↓
disk finishes operation
      ↓
process wakes up
```

During this time the process **cannot run and cannot handle signals immediately**.

---

# 3. Why Signals Cannot Interrupt D State

Signals require the process to return to **user mode** so the kernel can deliver the signal.

But during D state:

- the process is **blocked inside kernel code**
- the kernel is **waiting for hardware or driver completion**

Interrupting it could break kernel logic or leave resources inconsistent.

Therefore:

```
signals are marked pending
but not delivered yet
```

---

# 4. Example Scenario

```
process waiting for disk I/O
       ↓
process enters D state
       ↓
SIGKILL sent
       ↓
signal marked pending
       ↓
I/O completes
       ↓
process wakes up
       ↓
signal delivered
       ↓
process terminated
```

This is why sometimes:

```
kill -9 <pid>
```

appears to **not work immediately**.

---

# 5. Observing D State

Example using `ps`:

```
ps aux
```

Example output:

```
USER   PID  STAT COMMAND
root  1234   D   some_process
```

`STAT` column value:

```
D = uninterruptible sleep
```

In `top` you will also see:

```
D
```

---

# 6. Signal Masking

Signal masking allows a process to **temporarily block specific signals**.

Blocked signals are **not delivered immediately**.

Instead they become **pending signals**.

They are delivered once the signal is **unblocked**.

---

# 7. Why Signal Masking Is Used

Signal masking is used to **protect critical sections**.

Example problems without masking:

```
process updating shared data
       ↓
signal arrives
       ↓
handler modifies same data
       ↓
data corruption
```

Signal masking prevents signals from interrupting sensitive operations.

---

# 8. Example of Signal Masking

Block `SIGINT`:

```c
#include <signal.h>

sigset_t set;

sigemptyset(&set);
sigaddset(&set, SIGINT);

sigprocmask(SIG_BLOCK, &set, NULL);
```

Now `SIGINT` will **not be delivered**.

It becomes **pending**.

---

# 9. Unblocking Signals

To allow the signal again:

```c
sigprocmask(SIG_UNBLOCK, &set, NULL);
```

If a blocked signal is pending:

```
it will be delivered immediately after unblocking
```

---

# 10. Signal Masking Flow

```
signal blocked
      ↓
signal sent
      ↓
signal marked pending
      ↓
signal unblocked
      ↓
signal delivered
```

---

# 11. Difference: D State vs Signal Masking

| Feature | D State | Signal Masking |
|------|---------|----------------|
| Controlled by | kernel | process |
| Purpose | wait for kernel I/O | protect critical sections |
| Signals handled | delayed until wakeup | delayed until unblocked |
| Can process run? | no | yes |

---

# 12. Key Takeaways

- **D state** means the process is in **uninterruptible sleep** waiting for kernel I/O.
- Even `SIGKILL` cannot terminate a process immediately in D state.
- The signal becomes **pending** and is handled when the process wakes up.
- **Signal masking** is used by programs to temporarily block signals.
- Masked signals become **pending** until they are unblocked.

  # sigprocmask() — Parameters Explanation

`sigprocmask()` is used to **examine or change the signal mask of the calling process**.

The **signal mask** is the set of signals that are **currently blocked**.

---

# Function Prototype

```c
#include <signal.h>

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
```

---

# Parameters

| Parameter | Type | Meaning |
|----------|------|--------|
| `how` | `int` | Operation specifying how to modify the signal mask |
| `set` | `const sigset_t *` | Pointer to a set of signals to apply |
| `oldset` | `sigset_t *` | Stores the previous signal mask |

---

# 1. `how` Parameter

Controls **how the signal mask will change**.

Possible values:

| Value | Meaning |
|------|--------|
| `SIG_BLOCK` | Add signals in `set` to the mask (block them) |
| `SIG_UNBLOCK` | Remove signals in `set` from the mask |
| `SIG_SETMASK` | Replace the entire signal mask with `set` |

Example:

```
SIG_BLOCK → block these signals
SIG_UNBLOCK → unblock these signals
SIG_SETMASK → overwrite current mask
```

---

# 2. `set` Parameter

Pointer to a **signal set** (`sigset_t`).

This specifies **which signals are affected**.

Example creation:

```c
sigset_t set;

sigemptyset(&set);
sigaddset(&set, SIGINT);
```

This creates a set containing:

```
SIGINT
```

---

# 3. `oldset` Parameter

If not `NULL`, the previous signal mask is stored here.

This is useful for **restoring the original mask later**.

Example:

```c
sigset_t oldset;

sigprocmask(SIG_BLOCK, &set, &oldset);
```

Now:

```
oldset = previous mask
```

---

# Example Program

Block `SIGINT` temporarily.

```c
#include <stdio.h>
#include <signal.h>

int main() {

    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    sigprocmask(SIG_BLOCK, &set, NULL);

    printf("SIGINT blocked\n");

    sleep(10);

    sigprocmask(SIG_UNBLOCK, &set, NULL);

    printf("SIGINT unblocked\n");

    return 0;
}
```

Behavior:

```
Ctrl+C during first 10 seconds → ignored
after unblocking → signal works
```

---

# Typical Usage Pattern

Programs often:

```
save old mask
block signals
critical section
restore old mask
```

Example:

```c
sigset_t set, old;

sigemptyset(&set);
sigaddset(&set, SIGINT);

sigprocmask(SIG_BLOCK, &set, &old);

/* critical section */

sigprocmask(SIG_SETMASK, &old, NULL);
```

---

# Return Value

| Return | Meaning |
|------|--------|
| `0` | success |
| `-1` | error |

---

# Important Notes

- Only affects the **calling process or thread**.
- Some signals **cannot be blocked**:

```
SIGKILL
SIGSTOP
```

The kernel always delivers them.

---

# Summary

```
sigprocmask(how, set, oldset)
```

| Parameter | Role |
|------|------|
| `how` | how the mask should change |
| `set` | which signals to affect |
| `oldset` | store previous mask |
