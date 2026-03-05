# 📙 Hashing & Probing Techniques: Reference & Examples

A practical summary of hashing methods and probing strategies for hash tables.

---

## 1. Integer Hashing Techniques

| Technique                | Formula / Example                             | Description                                                                            |
|--------------------------|-----------------------------------------------|----------------------------------------------------------------------------------------|
| **Direct Hashing**       | `index = H(k) = k`                           | Only use if key space is small & dense.                                                |
| **Subtraction Method**   | `index = H(k) = k - C`                       | Subtracts constant C (when all keys ≥ C).                                              |
| **Mid-Square Method**    | `index = middle_digits_of(k*k)`              | Square k, extract some middle digits/bits. Good for mixing digits.                     |
| **Modulo Division**      | `index = k % m`                              | Most common. Use a prime for m if possible.                                            |
| **Digit Extraction**     | Combine specified digits from key             | Use certain digit positions, helpful for structured keys (e.g., IDs).                  |
| **Folding Method**       | `index = (sum of key's groups) % m`          | Split key into parts, add or XOR, modulo table size.                                   |
| **Shifting Method**      | `index = (k >> r) % m`                       | Shift k right by r bits before modulo, scrambles bits.                                 |
| **Rotation Method**      | Bitwise rotate k, then modulo                | Rotates bits for more entropy before mod.                                              |
| **Pseudo-Random Method** | `y = a*k + c; index = y % m`                 | Linear congruence, a and c are constants/primes, m is table size.                      |

### Integer Hash Function Examples

```c
// --- Direct Hash ---
int hash(int k) { return k; } // for keys in 0..MAX

// --- Subtraction Method ---
int hash(int k) { return k - 1000; } // if keys >= 1000

// --- Mid-Square ---
int hash(int k) {
    int sq = k * k;
    return (sq / 100) % 100; // extract middle
}

// --- Modulo Division ---
int hash(int k) { return k % 97; } // 97 is prime

// --- Digit Extraction ---
int hash(int k) {
    int d2 = (k/1000000)%10, d5 = (k/1000)%10, d7 = (k/10)%10;
    return (d2 + d5 + d7) % 97;
}

// --- Folding Method ---
int hash(int k) { int g1 = k/10000, g2 = k%10000; return (g1+g2)%97; }

// --- Shifting/Rotation ---
int hash(int k) { return ((k >> 3) % 97); }
unsigned int rotate_left(unsigned int k, unsigned int bits) {
    return (k << bits) | (k >> (32-bits));
}
int hash_rot(int k) { return (rotate_left(k, 5) % 97); }

// --- Pseudo-Random ---
int hash(int k) { return ((73 * k + 97) % 97); }


---

## 2. String Hash Functions

| Name             | Formula                                                           | Description (Notes)                              |
|------------------|-------------------------------------------------------------------|--------------------------------------------------|
| **DJB2**         | `hash = 5381; for c in s: hash = hash*33 + c`                     | Simple, widely used in open source.              |
| **SDBM**         | `hash = 0; for c in s: hash = c + (hash << 6) + (hash << 16) - hash` | Fast, good avalanche characteristics.        |
| **Polynomial Rolling** | `hash = s[0]*p^(n-1) + s[1]*p^(n-2) + ... + s[n-1], mod m`  | Great for substrings, used in Rabin-Karp, p=31/33/37.  |

### String Hash C Code Examples

#### DJB2 (string)
```c
unsigned long hash_djb2(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}

####SDBM (string)
unsigned long hash_sdbm(const char *str) {
    unsigned long hash = 0;
    int c;
    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;
    return hash;
}

####Polynomial Rolling Hash (string)
unsigned long hash_polynomial(const char *str) {
    unsigned long hash = 0;
    unsigned long p = 31;
    unsigned long power = 1;
    for (const char *s = str; *s; ++s) {
        hash += (*s) * power;
        power *= p;
    }
    return hash;
}

typedef struct {
    int id;
    char name[32];
} Person;

// Hash: mix id and each byte of name
unsigned long hash_person(const Person *p) {
    unsigned long hash = p->id;
    unsigned long prime = 31;
    for (const char *s = p->name; *s; ++s)
        hash = hash * prime + (unsigned char)(*s);
    return hash;
}



---

## 4. Probing Techniques (with Examples)

Hash tables with **open addressing** need probing methods to resolve collisions when slots are full. Here are the most common:

| Technique           | Formula Example                           | Description                                |
|---------------------|-------------------------------------------|--------------------------------------------|
| **Linear Probing**  | `index = (hash(k) + p) % n`               | Checks next slot, then next, wraps around.  |
| **Quadratic Probing** | `index = (hash(k) + p*p) % n`           | Checks slots at increasing square offsets.  |
| **Double Hashing**  | `index = (hash1(k) + p * hash2(k)) % n`   | Uses a second hash as the step size.        |

**Legend:**  
- `k` = key  
- `p` = probe number (0, 1, ... until slot found)  
- `n` = table size (preferably prime)  
- `hash()`, `hash1()`, `hash2()` = hash functions

---

### ✅ Linear Probing (C Example)

```c
// Insert/Search for key k, table size n
int linear_probe(int k, int p, int n) {
    return (hash(k) + p) % n; // probe sequence: idx, idx+1, idx+2, ...
}

### ✅ Quadratic Probing (C Example)
// Insert/Search for key k, table size n
int quadratic_probe(int k, int p, int n) {
    return (hash(k) + p*p) % n; // probe sequence: idx, idx+1^2, idx+2^2, ...
}

### ✅ Double Hashing (C Example)
// Insert/Search for key k, table size n
// hash1: main hash function; hash2: a different secondary hash, must NOT return zero!
int hash1(int k, int n) { return k % n; }
int hash2(int k, int n) { return 1 + (k % (n - 2)); }

int double_hash_probe(int k, int p, int n) {
    return (hash1(k, n) + p * hash2(k, n)) % n;
}

// Example Linear Probing Use in Insert or Search
int p = 0;
int idx;
do {
    idx = (hash(k) + p) % n;
    if (table[idx] is empty or matches key) break; // place or found
    p++;
} while (p < n);
