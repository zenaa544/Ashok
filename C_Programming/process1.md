Inherited (Copied) by Child Process after fork()

Process memory (address space)

Stack (local variables)

Heap (dynamic memory from malloc)

Global variables

Static variables

Environment variables

Signal dispositions (handlers)

Signal mask

Current working directory

Root directory

User ID (UID) and Group ID (GID)

Effective UID and GID

Process resource limits (rlimit)

File creation mask (umask)

Process group ID

Session ID (initially same as parent)

Shared / Referencing Same Kernel Object

Open file descriptors

File offsets (for open files)

File status flags (O_APPEND, O_NONBLOCK, etc.)

Open sockets

Pipes

Message queues (if already open)

Shared memory attachments

Memory-mapped regions (mmap)

Not Inherited / Different

Process ID (child gets new PID)

Parent process ID (PPID becomes parent’s PID)

Pending signals (not inherited)

CPU usage statistics

Timers (POSIX timers not inherited)
