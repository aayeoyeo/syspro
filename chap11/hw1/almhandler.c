#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

struct sigaction newact;
struct sigaction oldact;
void alarmHandler();

void mysignal(int signo, void (*handler)(int))
{
    newact.sa_handler = handler;
    sigfillset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(signo, &newact, &oldact);
}

int main()
{
    mysignal(SIGALRM, alarmHandler);
    alarm(5);
    short i = 0;
    while (1) {
        sleep(1);
        i++;
        printf("%d second\n", i);
    }
    printf("end\n");
}

void alarmHandler(int signo)
{
    printf("Wake up\n");
    exit(0);
}
