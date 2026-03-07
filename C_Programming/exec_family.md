# Unix exec() Family — Process Image Replacement

## 1. Overview

The **exec family of system calls** replaces the **current process image** with a new program.

Important concept:

```
fork() → creates a new process
exec() → replaces the program inside a process
```

After a successful `exec()`:

- the **same process continues**
- **PID remains unchanged**
- **program code, data, heap, and stack are replaced**

The process begins executing the **new program from its entry point (`main`)**.

---

# 2. Why exec() Exists

Unix separates **process creation** and **program execution**.

Typical pattern:

```
fork()
   ↓
child process created
   ↓
child calls exec()
   ↓
child becomes a different program
```

This allows:

- shells to run commands
- servers to launch workers
- programs to run other programs

Example:

```
shell
   ↓
fork()
   ↓
child process
   ↓
exec("ls")
```

The child becomes the `ls` program.

---

# 3. Basic exec Prototype

One of the simplest forms:

```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

Parameters:

| Parameter | Meaning |
|-----------|--------|
| pathname | program to execute |
| argv | argument list |
| envp | environment variables |

Example:

```c
char *args[] = {"ls", "-l", NULL};
execve("/bin/ls", args, NULL);
```

If successful:

```
current program is replaced by ls
```

The original program **never resumes**.

---

# 4. Important Property of exec()

If `exec()` succeeds:

```
it never returns
```

The only case it returns is **on failure**.

Example:

```c
execvp("ls", args);
printf("This runs only if exec fails\n");
```

---

# 5. What Changes After exec()

The following are **replaced**:

- program code
- data segment
- heap
- stack

The following remain **unchanged**:

| Property | Behavior |
|--------|----------|
| PID | unchanged |
| open file descriptors | remain open |
| process owner | unchanged |
| parent process | unchanged |

This is why shells can redirect files before `exec()`.

---

# 6. exec Family Variants

There are several exec functions.

| Function | Description |
|---------|-------------|
| execl | arguments passed as list |
| execv | arguments passed as array |
| execlp | searches PATH |
| execvp | array + PATH search |
| execle | allows custom environment |
| execve | lowest-level system call |

---

# 7. execl()

Arguments passed individually.

```c
execl("/bin/ls", "ls", "-l", NULL);
```

Structure:

```
execl(path, arg0, arg1, arg2, ..., NULL)
```

---

# 8. execv()

Arguments passed as an array.

```c
char *args[] = {"ls", "-l", NULL};

execv("/bin/ls", args);
```

Useful when arguments are generated dynamically.

---

# 9. execlp()

Searches the program in the **PATH environment variable**.

Example:

```c
execlp("ls", "ls", "-l", NULL);
```

Instead of specifying:

```
/bin/ls
```

---

# 10. execvp()

Most commonly used variant.

Arguments passed as an array and **PATH is searched**.

Example:

```c
char *args[] = {"ls", "-l", NULL};

execvp("ls", args);
```

---

# 11. execle()

Allows specifying environment variables.

Example:

```c
char *env[] = {"PATH=/bin", NULL};

execle("/bin/ls", "ls", "-l", NULL, env);
```

---

# 12. execve() (Kernel Interface)

`execve()` is the **actual system call** used by all other exec functions.

Prototype:

```c
int execve(const char *pathname,
           char *const argv[],
           char *const envp[]);
```

All other `exec*()` functions are **library wrappers around execve()**.

---

# 13. fork + exec Pattern

Typical Unix program execution:

```
Parent
   |
   | fork()
   |
Child
   |
   | exec()
   |
New program
```

Example:

```c
pid_t pid = fork();

if(pid == 0)
{
    char *args[] = {"ls", "-l", NULL};
    execvp("ls", args);
}
else
{
    wait(NULL);
}
```

Execution flow:

```
parent forks
   ↓
child created
   ↓
child execs ls
   ↓
parent waits
```

---

# 14. Why fork() + exec() is Used

Benefits:

- parent and child run independently
- child can modify environment before exec
- allows I/O redirection
- allows process supervision

This design is fundamental to **Unix shells**.

---

# 15. Example — Minimal Shell Behavior

A shell executes commands roughly like this:

```
user types command
      ↓
shell forks
      ↓
child execs command
      ↓
parent waits
```

Pseudo code:

```c
while(1)
{
    read_command();

    pid_t pid = fork();

    if(pid == 0)
    {
        execvp(command, args);
    }
    else
    {
        wait(NULL);
    }
}
```

---

# 16. Key Takeaways

- `exec()` replaces the **current process program**.
- The **PID does not change**.
- Memory (code, heap, stack) is replaced.
- Open file descriptors usually remain open.
- `exec()` **never returns if successful**.
- The common pattern is:

```
fork() → exec() → wait()
```

- All exec variants ultimately call **execve()**.
