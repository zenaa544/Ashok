# Hashing & Probing Techniques Reference

A handy summary for interviews, implementation, or revision! Mathematical formulas, brief descriptions, and tips included.

---

## 🏷️ Hashing Techniques

| Technique                  | Mathematical Formula / Example         | Description / Use Case                                                |
|----------------------------|----------------------------------------|-----------------------------------------------------------------------|
| **Direct Hashing**         | `index = H(k) = k`                     | Directly uses the key as index. Suitable for small, dense key sets.   |
| **Subtraction Method**     | `index = H(k) = k - C`                 | Uses key minus constant C (lower bound).                              |
| **Mid-Square Method**      | `index = (k * k) >> s & mask`          | Square key, extract middle digits/bits for index. Reduces clustering. |
| **Modulo Division**        | `index = k % m`                        | Most common; use a prime `m` for better distribution.                 |
| **Digit Extraction**       | Extract and combine selected digits     | Select parts of key (e.g., 2nd+4th digits); good for structured keys. |
| **Folding Method**         | Sum parts: `index = (sum(parts)) % m`  | Split key into equal-size parts, sum and mod. Good for long numbers.  |
| **Shifting Method**        | `index = (k >> r) % m`                 | Bitwise shift right by `r`, then mod.                                 |
| **Rotation Method**        | Bitwise rotate then mod                | Rotate bits before applying mod.                                      |
| **Pseudo-Random**          | `y = a*k + c; index = y % m`           | Linear congruential; `a`, `c` are primes or constants, for spreading. |

---

## 🏷️ Probing Techniques (for Open Addressing)

| Probing Method       | Formula                                         | Description / Notes                                         |
|----------------------|-------------------------------------------------|-------------------------------------------------------------|
| **Linear Probing**   | `H(k,p) = (H(k) + p) % n`                       | Steps by +1; may cause primary clustering.                  |
| **Quadratic Probing**| `H(k,p) = (H(k) + c1·p + c2·p²) % n`<br>Often: `H(k,p) = (H(k) + p^2) % n` | Jumps grow quadratically; reduces clustering.               |
| **Double Hashing**   | `H(k,p) = (H1(k) + p * H2(k)) % n`              | Uses step size from a second hash, best distribution.       |

**Where:**  
- `k` = key  
- `C` = constant  
- `m`, `n` = table size (typically, a prime number)  
- `p` = probe attempt (`0, 1, 2,...`)  
- `c1, c2` = nonzero constants  
- `H()`, `H1()`, `H2()` = hash functions

---

## 💎 Quick Examples

### Modulo Division (Standard Hash)
```c
int hash(int k, int m) { return k % m; }
