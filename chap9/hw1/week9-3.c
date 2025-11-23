#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_CMD 1024
#define MAX_ARG 64

int tokenize(char *buf, char *args[]) {
    int count = 0;
    char *token = strtok(buf, " \t\n");
    while (token != NULL && count < MAX_ARG - 1) {
        args[count++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[count] = NULL;
    return count;
}

int main() {
    char line[MAX_CMD];
    char *args[MAX_ARG];
    char *commands[MAX_ARG];
    
    while (1) {
        printf("[shell] ");
        if (fgets(line, sizeof(line), stdin) == NULL) break;
        
        line[strcspn(line, "\n")] = '\0';
        
        if (strcmp(line, "exit") == 0) break;
        if (strlen(line) == 0) continue;

        int cmd_count = 0;
        char *ptr = strtok(line, ";");
        while (ptr != NULL && cmd_count < MAX_ARG - 1) {
            commands[cmd_count++] = ptr;
            ptr = strtok(NULL, ";");
        }
        commands[cmd_count] = NULL;

        for (int i = 0; i < cmd_count; i++) {
            int background = 0;
            int redirect_in = 0;
            int redirect_out = 0;
            char *infile = NULL;
            char *outfile = NULL;

            int arg_count = tokenize(commands[i], args);
            if (arg_count == 0) continue;

            for (int j = 0; j < arg_count; j++) {
                if (strcmp(args[j], "&") == 0) {
                    background = 1;
                    args[j] = NULL;
                    break;
                } else if (strcmp(args[j], ">") == 0) {
                    redirect_out = 1;
                    outfile = args[j+1];
                    args[j] = NULL;
                    break;
                } else if (strcmp(args[j], "<") == 0) {
                    redirect_in = 1;
                    infile = args[j+1];
                    args[j] = NULL;
                    break;
                }
            }

            pid_t pid = fork();
            if (pid == 0) {
                if (redirect_out) {
                    int fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                }
                if (redirect_in) {
                    int fd = open(infile, O_RDONLY);
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                }
                
                execvp(args[0], args);
                perror("execvp error"); 
				exit(1);
            } else if (pid > 0) {
                if (!background) {
                    wait(NULL);
                } else {
                    printf("[Backgound process %d]\n", pid);
                }
            } else {
                perror("fork error");
            }
        }
    }
    return 0;
}
