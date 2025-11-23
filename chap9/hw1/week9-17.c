#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define MAXARG 10

void sigchld_handler(int sig) {
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("[%d] child process end %d\n", getpid(), pid);
    }
}

int main() {
    char cmd[256];
    char *args[MAXARG];
    char *token;
    char *saveptr;
    int pid, status;
    
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &sa, NULL);

    while (1) {
        printf("Pls input cmd : ");
        
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) break;
        
        cmd[strcspn(cmd, "\n")] = '\0';
        
        if (strlen(cmd) == 0) continue;
        if (strcmp(cmd, "exit") == 0) {
            printf("Exit\n");
            break;
        }

        int arg_count = 0;
        int background = 0;

        token = strtok_r(cmd, " ", &saveptr);
        while (token != NULL && arg_count < MAXARG - 1) {
            if (strcmp(token, "&") == 0) {
                background = 1;
            } else {
                args[arg_count++] = token;
            }
            token = strtok_r(NULL, " ", &saveptr);
        }
        args[arg_count] = NULL;

        if (arg_count == 0) continue;

        printf("[%d] Parent process start\n", getpid());
        
        if (background) {
            pid = fork();
            if (pid == 0) {
                printf("[%d] child process start\n", getpid());
                execvp(args[0], args);
                exit(0); 
            }
            sleep(1);
            printf("SUCCESS\n");
        } else {
            signal(SIGCHLD, SIG_DFL);
            
            pid = fork();
            if (pid == 0) {
                execvp(args[0], args);
                exit(127);
            } else if (pid > 0) {
                waitpid(pid, &status, 0);
                
                if (WIFEXITED(status) && WEXITSTATUS(status) == 127) {
                    printf("Parent process end\n");
                    printf("Exit\n");
                    return 0; 
                } else {
                    printf("SUCCESS\n");
                }
                
                sigaction(SIGCHLD, &sa, NULL);
            }
        }
		printf("\n");
    }
    return 0;
}
