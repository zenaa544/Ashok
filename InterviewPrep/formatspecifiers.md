| Specifier | Prints Type                     | Example Use                         |
|-----------|---------------------------------|-------------------------------------|
| %d        | int (signed decimal)            | printf("%d", -42);                  |
| %i        | int (signed decimal)            | printf("%i", 42);                   |
| %u        | unsigned int                    | printf("%u", 42u);                  |
| %ld       | long int                        | printf("%ld", 123456789L);          |
| %lu       | unsigned long int               | printf("%lu", 123456789ul);         |
| %lld      | long long int                   | printf("%lld", 1234567890123LL);    |
| %llu      | unsigned long long int          | printf("%llu", 1234567890123ULL);   |
| %f        | float/double                    | printf("%f", 3.14);                 |
| %e/%E     | float/double (scientific)       | printf("%e", 123.45);               |
| %g/%G     | float/double (shortest)         | printf("%g", 123.45);               |
| %c        | char                            | printf("%c", 'A');                  |
| %s        | string                          | printf("%s", "hello");              |
| %p        | pointer (address)               | printf("%p", ptr);                  |
| %x/%X     | unsigned int (hexadecimal)      | printf("%x", 0x7B);                 |
| %o        | unsigned int (octal)            | printf("%o", 123);                  |
| %%        | percent sign                    | printf("%%");                       |
| %zd       | ssize_t                         | printf("%zd", size_val);            |
| %zu       | size_t                          | printf("%zu", size_val);            |
| %td       | ptrdiff_t (signed)              | printf("%td", diff);                |
| %tu       | ptrdiff_t (unsigned)            | printf("%tu", diff);                |
