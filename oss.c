#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>

void print_help() {
    printf("Usage: oss [-h] [-n proc] [-s simul] [-t iter]\n");
    printf("  -h        Print this help message\n");
    printf("  -n proc   Total number of child processes to launch\n");
    printf("  -s simul  Maximum simultaneous processes\n");
    printf("  -t iter   Number of iterations for each child\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    int num_procs = 5, max_simul = 3, num_iter = 7;
    int opt;

    // different input cases handled
    while ((opt = getopt(argc, argv, "hn:s:t:")) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                break;
            case 'n':
                num_procs = atoi(optarg);
                break;
            case 's':
                max_simul = atoi(optarg);
                break;
            case 't':
                num_iter = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Invalid option. Use -h for help.\n");
                exit(EXIT_FAILURE);
        }
    }

    printf("OSS starting with %d processes, %d max simultaneous, %d iterations.\n",
           num_procs, max_simul, num_iter);

    int active_procs = 0;

    for (int i = 0; i < num_procs; i++) {
        if (active_procs >= max_simul) {
            wait(NULL);  // Wait for a process to finish if max_simul is reached
            active_procs--;
        }

        pid_t pid = fork();
        if (pid == 0) { // Child process
            char iter_str[10];
            snprintf(iter_str, sizeof(iter_str), "%d", num_iter);
            execl("./user", "user", iter_str, (char *)NULL);
            perror("execl failed");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        } else {
            active_procs++;
        }
    }

    // Wait for all remaining child processes
    while (active_procs > 0) {
        wait(NULL);
        active_procs--;
    }

    printf("All processes completed.\n");
    return 0;
}
