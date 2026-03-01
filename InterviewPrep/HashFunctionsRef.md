| Hash Function Name | Key Type      | Common Use Case                 | Core Idea / Description                      |
|--------------------|--------------|---------------------------------|----------------------------------------------|
| Division           | Integer      | Basic hash tables, fast lookup  | `hash(k) = k % table_size`                   |
| Multiplication     | Integer      | Hash tables, low collision      | `hash(k) = floor(m * frac(k * A))`           |
| Folding            | Integer      | Large numbers, registration IDs | Split into parts, add/combine, then mod      |
| Mid-square         | Integer      | Specialized tables              | Hash middle digits/bits of squared key       |
| Polynomial rolling | String       | Strings, substrings (e.g., Rabin-Karp) | Combine chars with powers of a prime         |
| DJB2               | String       | General-purpose string hash     | `hash = hash * 33 + c` per character         |
| SDBM               | String       | General-purpose string hash     | `hash = c + (hash << 6) + (hash << 16) - hash` |
| FNV                | String/Binary| Short strings, binary data      | Fast, lightweight, good distribution         |
| MurmurHash         | Any/Binary   | Hash tables, hash maps (fast, non-crypto) | Blockwise mix of input, good avalanche       |
| CityHash/XXHash    | Any/Binary   | Large-scale hashing, logs       | Super-fast, very low collision rate          |
| SHA (e.g., SHA-256)| Any/Binary   | Cryptographic, checksums        | Secure, not used for hash tables (slow)      |
| MD5                | Any/Binary   | Old checksums (not secure)      | Weak cryptography/legacy, rarely for general |
| Universal Hashing  | Any          | Theoretical, security           | Randomized, prevents adversarial collision   |

# Compact Reference for Hash Functions
