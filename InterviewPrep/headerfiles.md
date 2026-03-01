| Operation Type      | Header File(s)                                            | Example Functions                  |
|---------------------|----------------------------------------------------------|------------------------------------|
| String              | `<string.h>`                                             | `strcpy`, `strcmp`, `strlen`       |
| Standard I/O        | `<stdio.h>`                                              | `printf`, `scanf`, `fopen`         |
| Low-level I/O       | `<unistd.h>`                                             | `read`, `write`, `close`           |
| File Control        | `<fcntl.h>`                                              | `open`, `fcntl`                    |
| File/Dir Status     | `<sys/types.h>`, `<sys/stat.h>`                          | `stat`, `fstat`, `chmod`           |
| Memory Management   | `<stdlib.h>`                                             | `malloc`, `free`, `realloc`        |
| Process Control     | `<unistd.h>`, `<sys/wait.h>`                             | `fork`, `exec`, `wait`, `getpid`   |
| Time/Date           | `<time.h>`                                               | `time`, `localtime`, `strftime`    |
| Error Handling      | `<errno.h>`, `<string.h>`                                | `errno`, `strerror`                |
| Networking          | `<sys/socket.h>`, `<netinet/in.h>`, `<arpa/inet.h>`      | `socket`, `bind`, `inet_ntoa`      |
| Character Handling  | `<ctype.h>`                                              | `isalpha`, `isdigit`, `toupper`    |
| Debugging           | `<assert.h>`                                             | `assert`                           |
| Math                | `<math.h>`                                               | `sin`, `pow`, `sqrt`               |
