# Unix Process States, fork(), Zombie Processes, and Child Reaping

## 1. Overview

In Unix-like operating systems, processes transition through several states during their lifecycle. Understanding these states is essential for system programming and debugging process behavior.

Topics covered:

- Process states
- Process creation with `fork()`
- Zombie processes
- Child process cleanup
- `wait()` vs `waitpid()`
- Handling multiple children
- Non-blocking child reaping

---

# 2. Process States in Unix/Linux

Processes move between several kernel states during execution.

| State | Description |
|------|-------------|
| Running | Process is executing or ready to run |
| Interruptible Sleep | Waiting for an event, signals can wake it |
| Uninterruptible Sleep | Waiting for kernel I/O, signals ignored |
| Stopped | Suspended via signal (debugger/job control) |
| Zombie | Process exited but parent hasn't collected status |
| Dead | Process fully removed from process table |

---

# 2.1 Running State

The process is either:

- currently executing on CPU
- ready to run and waiting for CPU

Kernel state:

```
TASK_RUNNING
```

The **scheduler** decides which runnable process executes.

---

# 2.2 Interruptible Sleep

Process waits for an event and **can be awakened by signals**.

Examples:

- waiting for user input
- waiting on pipe/socket
- `sleep()`
- blocking I/O

Kernel state:

```
TASK_INTERRUPTIBLE
```

Signals can wake the process.

---

# 2.3 Uninterruptible Sleep

Process waits for **kernel resources or hardware I/O**.

Kernel state:

```
TASK_UNINTERRUPTIBLE
```

Common causes:

- disk I/O
- NFS filesystem operations
- device driver operations
- memory paging

Shown in `ps` or `top` as:

```
D state (disk sleep)
```

Important behavior:

Signals such as `kill -9` **cannot terminate the process immediately** while it is in this state.

---

# 2.4 Stopped State

Process execution is paused.

Examples:

- debugger breakpoints
- job control (`Ctrl+Z`)

Kernel state:

```
TASK_STOPPED
```

---

# 2.5 Zombie State

Occurs when:

```
child exits
parent has not yet called wait()
```

Kernel state:

```
TASK_ZOMBIE
```

Zombie processes:

- consume **no CPU**
- consume **no memory**
- occupy **only a process table entry**

---

# 3. Process Creation with fork()

Processes create children using:

```c
pid_t fork();
```

Return values:

| Return Value | Meaning |
|--------------|--------|
| 0 | Child process |
| >0 | Parent receives child PID |
| -1 | Fork failed |

Example:

```c
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
```

Process tree example:

```
Parent
   |
   |--- Child1
   |--- Child2
   |--- Child3
```

Each child is an **independent process**.

---

# 4. Process Termination

A process terminates via:

- `exit()`
- returning from `main()`
- receiving a termination signal

When a child exits:

1. Kernel frees memory
2. Kernel closes open files
3. Kernel stores exit status
4. Process enters **zombie state**
5. Parent receives **SIGCHLD signal**

---

# 5. Zombie Processes

## When does a process become zombie?

When:

```
child exits
parent has not called wait()
```

Lifecycle:

```
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
```

Reason zombies exist:

The kernel keeps the zombie so the parent can retrieve:

- exit status
- termination signal
- resource usage

Example child exit:

```c
exit(5);
```

Parent retrieves status:

```c
wait(&status);
```

---

# 6. Problems if Zombies Accumulate

If the parent **never calls wait()**:

- zombie entries remain
- process table fills
- system may reach PID limits

Possible error:

```
fork: Resource temporarily unavailable
```

---

# 7. How Zombies Are Handled

## Case 1: Parent calls wait()

Normal cleanup:

```
child exits
   ↓
zombie created
   ↓
parent calls wait()
   ↓
zombie removed
```

---

## Case 2: Parent dies

Child becomes **orphan**.

The kernel assigns the child to **PID 1 (init or systemd)**.

That process automatically calls `wait()`.

---

# 8. wait() System Call

Prototype:

```c
pid_t wait(int *status);
```

Behavior:

- blocks until **any child exits**
- returns **PID of terminated child**

Example:

```c
int status;
pid_t pid = wait(&status);
```

---

## Exit Status Macros

```
WIFEXITED(status)
WEXITSTATUS(status)
WIFSIGNALED(status)
WTERMSIG(status)
```

Example:

```c
if (WIFEXITED(status))
{
    printf("exit code %d\n", WEXITSTATUS(status));
}
```

---

# 9. waitpid() System Call

Prototype:

```c
pid_t waitpid(pid_t pid, int *status, int options);
```

Provides **more control than wait()**.

---

## pid Parameter

| Value | Meaning |
|------|---------|
| >0 | wait for specific child |
| -1 | wait for any child |
| 0 | wait for same process group |
| < -1 | wait for specific process group |

---

## options Parameter

| Option | Meaning |
|------|---------|
| 0 | blocking wait |
| WNOHANG | non-blocking |
| WUNTRACED | report stopped child |
| WCONTINUED | report resumed child |

---

# 10. Blocking vs Non-blocking

## wait()

Always blocking.

Equivalent to:

```
waitpid(-1, &status, 0)
```

---

## Non-blocking waitpid()

```c
waitpid(-1, &status, WNOHANG);
```

Return values:

| Return | Meaning |
|------|---------|
| >0 | child exited |
| 0 | no child exited |
| -1 | error |

---

# 11. Handling Multiple Children

One `wait()` call reaps **only one child**.

Example:

```
Child1 Z
Child2 Z
Child3 Z
```

Calling `wait()` once:

```
Child1 removed
Child2 Z
Child3 Z
```

Correct cleanup pattern:

```c
while(wait(NULL) > 0);
```

or

```c
while(waitpid(-1,NULL,0) > 0);
```

---

# 12. Non-blocking Child Reaping

Used in servers or event loops.

Example:

```c
while(waitpid(-1,NULL,WNOHANG) > 0)
{
}
```

This removes all zombie children **without blocking**.

---

# 13. Using SIGCHLD

The kernel sends **SIGCHLD** when a child exits.

Example signal handler:

```c
void handler(int sig)
{
    while(waitpid(-1,NULL,WNOHANG) > 0);
}
```

Register handler:

```c
signal(SIGCHLD, handler);
```

---

# 14. Typical Production Pattern

Production servers avoid heavy work inside signal handlers.

Instead:

```
SIGCHLD received
      ↓
set flag
      ↓
main loop detects flag
      ↓
call waitpid()
```

Example:

```c
while(1)
{
    if(child_exit_flag)
    {
        while(waitpid(-1,NULL,WNOHANG) > 0);
    }

    handle_events();
}
```

---

# 15. Key Takeaways

- `fork()` creates a child process.
- When a child exits it becomes a **zombie** until the parent calls `wait()`.
- Zombies store **exit status information**.
- `wait()` blocks for **any child**.
- `waitpid()` allows **specific or non-blocking waits**.
- `WNOHANG` enables **non-blocking child cleanup**.
- Each zombie requires **one wait() call** to be removed.
- Proper programs periodically **reap children** to avoid zombie accumulation.
