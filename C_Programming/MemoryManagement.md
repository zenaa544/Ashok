# Memory Management Basics (Before Virtual Address Space)

Before understanding **Virtual Address Space**, we must understand the **problems that existed in earlier memory management systems**. These problems led to the development of **virtual memory**.

Key concepts to understand:

- Internal Fragmentation
- External Fragmentation
- Thrashing
- Why Virtual Addressing is Needed

---

# 1. Why Memory Management is Needed

In a computer system:

```
CPU executes programs
        ↓
Programs need memory
        ↓
Multiple programs share RAM
```

The operating system must:

- allocate memory to processes
- protect processes from each other
- efficiently utilize memory
- allow multiple programs to run simultaneously

Early systems used **simple memory allocation**, which created several problems.

---

# 2. Fragmentation

Fragmentation occurs when **memory becomes inefficiently used**.

Two main types exist:

```
1. Internal Fragmentation
2. External Fragmentation
```

---

# 3. Internal Fragmentation

## When Internal Fragmentation Happens

Internal fragmentation typically occurs in systems where **memory is allocated in fixed-size blocks**, such as:

- **Fixed partition memory allocation**
- **Paging systems** (small amount possible due to page size)

In these systems, a process must occupy an entire partition or block even if it does not need all of it.

---

## Definition

Internal fragmentation occurs when:

```
allocated memory block > requested memory
```

The unused memory **inside the allocated block** is wasted.

---

## Example

Assume memory is allocated in **fixed-size blocks of 8 KB**.

Process requests:

```
Process A → needs 6 KB
```

Memory allocated:

```
8 KB block
```

Usage:

```
6 KB used
2 KB wasted
```

Diagram:

```
Allocated Block (8 KB)

[ Used 6 KB ][ Wasted 2 KB ]
```

That **2 KB cannot be used by other processes**.

---

# 4. External Fragmentation

## When External Fragmentation Happens

External fragmentation occurs in systems where **memory is allocated dynamically with variable-sized partitions**, such as:

- **Dynamic partition memory allocation**
- **Segmentation systems**

In these systems, processes are allocated memory **exactly according to their size**, but when processes terminate, the freed memory blocks may become scattered throughout memory.

---

## Definition

External fragmentation occurs when **free memory is scattered into small pieces**.

Even if **total free memory is sufficient**, it may not be **contiguous**.

---

## Example

Memory layout:

```
[Process A][Free][Process B][Free][Process C][Free]
```

Free spaces:

```
2 KB + 3 KB + 1 KB = 6 KB total free memory
```

Now a process requests:

```
5 KB
```

But the **largest contiguous free block** is only:

```
3 KB
```

Therefore:

```
allocation fails
```

Even though **6 KB total free memory exists**.

---

## Diagram

```
Memory Layout

| A | free | B | free | C | free |
     2KB      3KB      1KB

Total Free = 6 KB
Largest Block = 3 KB
```

Request:

```
Process needs 5 KB
```

Result:

```
Allocation fails
```

---

# 5. Compaction (Solution to External Fragmentation)

To solve external fragmentation:

```
move processes
combine free spaces
```

Example:

Before compaction:

```
| A | free | B | free | C | free |
```

After compaction:

```
| A | B | C | free free free |
```

Now the free space becomes **one large block**.

However, compaction is:

- expensive
- requires moving processes in memory

---

# 6. Thrashing

Thrashing occurs in **virtual memory systems** when the system spends **more time swapping pages than executing programs**.

---

## What Happens During Thrashing

```
Process needs page
        ↓
Page not in memory
        ↓
Page fault occurs
        ↓
OS loads page from disk
        ↓
Another page removed
        ↓
Next instruction needs removed page
        ↓
Another page fault
```

This creates a loop.

---

## Result

```
CPU mostly idle
Disk heavily used
System extremely slow
```

---

## Thrashing Cycle

```
Page Fault
     ↓
Disk I/O
     ↓
Page Replacement
     ↓
Another Page Fault
     ↓
More Disk I/O
```

---

## When Thrashing Happens

Thrashing occurs when:

```
too many processes
not enough physical memory
```

or

```
working set of processes > available RAM
```

---

# 7. Why Virtual Addressing Was Introduced

Earlier memory systems had major limitations:

```
1. Programs must fit entirely in RAM
2. Fragmentation wastes memory
3. Limited memory isolation
4. Difficult memory allocation
```

Virtual addressing solves these problems.

---

# 8. Goals of Virtual Memory

Virtual memory provides:

### 1. Large Address Space

Programs can use more memory than physical RAM.

Example:

```
Program sees 4 GB memory
Actual RAM = 8 GB shared by many processes
```

---

### 2. Process Isolation

Each process gets its **own virtual address space**.

```
Process A cannot access memory of Process B
```

---

### 3. Efficient Memory Usage

Only **needed pages** are loaded into RAM.

```
Program size = 1 GB
Pages loaded = maybe 50 MB
```

---

### 4. Elimination of External Fragmentation

Paging divides memory into **fixed-size pages**, preventing external fragmentation.

---

# 9. Summary

| Concept | Meaning |
|-------|--------|
| Internal Fragmentation | wasted space inside allocated block |
| External Fragmentation | free memory scattered in small pieces |
| Thrashing | excessive paging causing system slowdown |
| Virtual Addressing | abstraction allowing processes to use virtual memory |

---

# Next Step

After these concepts, the next logical topics are:

```
1. Virtual Address Space
2. Logical vs Physical Address
3. Address Translation
4. Paging
5. Page Tables
```

These explain **how operating systems implement virtual memory**.
