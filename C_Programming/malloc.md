# Heap in a Unix/Linux Process

## 1. What the Heap Is
The **heap** is a region of a process's **virtual address space** used for **dynamic memory allocation**.

Memory returned by the following functions typically comes from the heap:

- malloc()
- calloc()
- realloc()
- free()

Characteristics:
- Part of the **process virtual address space**
- Typically **grows upward**
- Managed mostly by a **user-space allocator (e.g., glibc malloc)**

---

# 2. Heap Ownership

The heap is **private to a process**.

- Each process has its **own heap**
- Other processes **cannot access it**
- Isolation is enforced by **virtual memory**

Exception: memory explicitly shared using mechanisms such as:

mmap(MAP_SHARED)

Normal heap allocations are **not shared between processes**.

---

# 3. Heap at Process Start

When a process starts (after exec):

- The kernel creates the process **virtual address space**
- A **small initial heap region** is created
- This region is mostly **unused**
- It is available for the memory allocator

Typical simplified layout:

Low Address
--------------------------------
Code (.text)
Data (.data)
BSS
Heap (initial small area)
--------------------------------
Unused address space
--------------------------------
Stack
High Address

The heap grows **upward** when needed.

---

# 4. Who Manages Heap Allocations

Heap allocation works in **two layers**.

## Kernel
Provides memory pages using:

- brk()
- sbrk()
- sometimes mmap()

The kernel works with **pages** (typically 4 KB).

## User-space allocator

The C runtime allocator (glibc malloc) manages:

- allocation requests
- free lists
- fragmentation
- reuse of freed blocks

Most malloc() calls **do not trigger a system call**.

---

# 5. Program Break

The **program break** is a pointer maintained by the kernel that marks:

end of the heap

Everything **below the program break** belongs to the heap.

Example:

Heap memory
-----------------
Program Break
-----------------
Unused address space

When the program break moves upward, the heap **grows**.

---

# 6. System Calls Controlling Heap Size

## brk()

Sets the program break to a specific address.

int brk(void *addr);

## sbrk()

Moves the program break relative to the current position.

void *sbrk(intptr_t increment);

Example:

sbrk(4096)

This increases the heap size by **one page (4 KB)**.

---

# 7. What Happens During malloc()

Typical flow:

malloc()
   ↓
glibc allocator checks free heap memory
   ↓
if enough space → memory returned
   ↓
if not enough
   ↓
allocator calls sbrk()/brk()
   ↓
kernel increases heap size

---

# 8. Kernel Allocation Granularity

The kernel allocates memory in **pages**, not small chunks.

Example:

malloc(100)

The allocator might request:

4096 bytes

from the kernel.

Then the allocator splits it internally:

4096 page
 ├── 100 bytes → returned to user
 └── remaining bytes → kept in allocator free lists

The kernel **never handles small allocations directly**.

---

# 9. Lazy Physical Memory Allocation

Even after heap expansion:

virtual memory exists
physical memory may not yet exist

Physical pages are usually allocated when the process **first accesses the memory**.

This mechanism is called:

demand paging

---

# 10. Large Allocations

For large allocations, malloc() often uses:

mmap()

instead of expanding the heap.

Example:

malloc(10 MB)
    ↓
allocator calls mmap()
    ↓
separate memory mapping created

This memory:

- is **not part of the heap**
- can be **returned directly to the kernel**

---

# 11. Heap Growth Example

Before allocation:

Heap
-----------
free memory
-----------
Program Break

After heap expansion:

Heap
-----------
allocated blocks
-----------
free memory
-----------
Program Break (moved upward)

---

# 12. Key Points

- Heap is **process private**
- Used for **dynamic memory allocation**
- Managed by **user-space allocator**
- Kernel expands heap using **brk()/sbrk()**
- Kernel allocates memory in **pages**
- Physical memory is often allocated **lazily**
- Large allocations may use **mmap() instead of heap**
