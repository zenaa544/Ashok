# Unix Signal System Calls — Complete Guide

This document explains four important Unix signal-related system calls:

- `signal()`
- `sigprocmask()`
- `sigaction()`
- `kill()`

For each system call we cover:

- what it is
- purpose
- syntax
- parameters
- usage
- example program

---

# 1. signal()

## What is signal()

`signal()` is used to **define how a process handles a particular signal**.

It allows a program to:

- execute a **custom signal handler**
- **ignore the signal**
- restore the **default behavior**

This is the **older interface** for signal handling.

Modern POSIX programs prefer **`sigaction()`** because it is more reliable.

---

# Syntax

```c
#include <signal.h>

void (*signal(int signum, void (*handler)(int)))(int);
```

Simplified:

```
signal(signal_number, handler_function)
```

---

# Parameters

| Parameter | Meaning |
|-----------|--------|
| `signum` | signal number (e.g., `SIGINT`, `SIGTERM`) |
| `handler` | function or action to execute |

---

# Handler Options

| Handler | Meaning |
|--------|--------|
| `SIG_DFL` | default signal behavior |
| `SIG_IGN` | ignore the signal |
| function pointer | custom signal handler |

---

# Example Program

Handling **Ctrl+C (SIGINT)**.

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    printf("SIGINT received\n");
}

int main()
{
    signal(SIGINT, handler);

    while(1)
    {
        printf("Program running...\n");
        sleep(2);
    }
}
```

---

# Execution Flow

```
Ctrl+C pressed
      ↓
SIGINT generated
      ↓
signal handler executes
      ↓
program continues
```

---

# Ignoring a Signal

```c
signal(SIGINT, SIG_IGN);
```

Now pressing **Ctrl+C** does nothing.

---

# Restoring Default Behavior

```c
signal(SIGINT, SIG_DFL);
```

---

# Limitations of signal()

Problems with `signal()`:

- behavior differs across Unix systems
- handler may reset automatically
- race conditions possible

Because of this, modern programs prefer:

```
sigaction()
```

---

# 2. sigprocmask()

## What is sigprocmask()

`sigprocmask()` is used to **examine or modify the signal mask of a process**.

The **signal mask** is the set of signals that are **currently blocked**.

Blocked signals are **not delivered immediately**.

They become **pending signals** and are delivered when unblocked.

---

# Syntax

```c
#include <signal.h>

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
```

---

# Parameters

| Parameter | Meaning |
|-----------|--------|
| `how` | how the mask should change |
| `set` | signals to modify |
| `oldset` | stores previous signal mask |

---

# Values for how

| Value | Meaning |
|------|--------|
| `SIG_BLOCK` | add signals to mask |
| `SIG_UNBLOCK` | remove signals from mask |
| `SIG_SETMASK` | replace current mask |

---

# Signal Set Type

Signals are stored in a structure:

```
sigset_t
```

Functions used with signal sets:

| Function | Purpose |
|---------|--------|
| `sigemptyset()` | create empty set |
| `sigfillset()` | fill set with all signals |
| `sigaddset()` | add signal to set |
| `sigdelset()` | remove signal from set |

---

# Example Program

Block `SIGINT` temporarily.

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    sigprocmask(SIG_BLOCK, &set, NULL);

    printf("SIGINT blocked for 10 seconds\n");

    sleep(10);

    sigprocmask(SIG_UNBLOCK, &set, NULL);

    printf("SIGINT unblocked\n");

    while(1);
}
```

---

# Execution Flow

```
Ctrl+C pressed
      ↓
signal blocked
      ↓
signal marked pending
      ↓
signal unblocked
      ↓
signal delivered
```

---

# Important Notes

Some signals **cannot be blocked**:

```
SIGKILL
SIGSTOP
```

The kernel always delivers them.

---

# 3. sigaction()

## What is sigaction()

`sigaction()` is the **modern POSIX interface for signal handling**.

It provides:

- reliable signal handling
- better control over signal behavior
- ability to set flags and masks

Most real-world programs use **`sigaction()` instead of `signal()`**.

---

# Syntax

```c
#include <signal.h>

int sigaction(int signum,
              const struct sigaction *act,
              struct sigaction *oldact);
```

---

# Parameters

| Parameter | Meaning |
|-----------|--------|
| `signum` | signal number |
| `act` | new signal action |
| `oldact` | previous signal action |

---

# struct sigaction

```c
struct sigaction
{
    void (*sa_handler)(int);
    sigset_t sa_mask;
    int sa_flags;
};
```

---

# Fields of struct sigaction

| Field | Purpose |
|------|--------|
| `sa_handler` | handler function |
| `sa_mask` | signals blocked during handler execution |
| `sa_flags` | special options |

---

# Example Program

Handling `SIGINT` using `sigaction()`.

```c
#include <stdio.h>
#include <signal.h>

void handler(int sig)
{
    printf("SIGINT caught\n");
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    while(1);
}
```

---

# Execution Flow

```
Ctrl+C pressed
      ↓
SIGINT generated
      ↓
kernel delivers signal
      ↓
handler() executes
```

---

# Why sigaction() is Better

Advantages over `signal()`:

- consistent POSIX behavior
- handler not reset automatically
- supports signal masking
- supports flags like `SA_RESTART`

---

# 4. kill()

## What is kill()

`kill()` is used to **send a signal to another process**.

It is commonly used for:

- terminating processes
- controlling processes
- inter-process communication

Despite its name, it can send **any signal**, not just `SIGKILL`.

---

# Syntax

```c
#include <signal.h>

int kill(pid_t pid, int sig);
```

---

# Parameters

| Parameter | Meaning |
|-----------|--------|
| `pid` | target process or process group |
| `sig` | signal to send |

---

# PID Meaning

| PID Value | Target |
|-----------|--------|
| `> 0` | specific process |
| `0` | processes in same process group |
| `-1` | all processes permitted |
| `< -1` | specific process group |

---

# Example

Send `SIGTERM` to a process.

```c
#include <signal.h>

int main()
{
    kill(1234, SIGTERM);
}
```

---

# Example — Send Signal to Self

```c
#include <signal.h>
#include <unistd.h>

int main()
{
    kill(getpid(), SIGINT);
}
```

---

# Typical Real-World Example

Command in shell:

```
kill -9 1234
```

What happens internally:

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

# Complete Signal Handling Flow

```
signal occurs
      ↓
kernel checks signal mask
      ↓
if blocked → signal pending
      ↓
if unblocked → signal delivered
      ↓
handler installed using signal()/sigaction()
      ↓
handler executes
```

---

# Summary

| System Call | Purpose |
|-------------|--------|
| `signal()` | simple signal handler installation |
| `sigprocmask()` | block/unblock signals |
| `sigaction()` | advanced signal handling |
| `kill()` | send signals to processes |

---

# Key Concept

```
kill()        → send signal
sigprocmask() → block/unblock signal
signal()      → define handler (simple)
sigaction()   → define handler (advanced)
```

---
