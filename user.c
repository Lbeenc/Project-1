#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <iterations>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int iterations = atoi(argv[1]);
    pid_t pid = getpid();
    pid_t ppid = getppid();

    for (int i = 1; i <= iterations; i++) {
        printf("USER PID:%d PPID:%d Iteration:%d before sleeping\n", pid, ppid, i);
        sleep(1);
        printf("USER PID:%d PPID:%d Iteration:%d after sleeping\n", pid, ppid, i);
    }

    return EXIT_SUCCESS;
}
