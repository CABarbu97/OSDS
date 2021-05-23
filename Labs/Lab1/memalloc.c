#include <stdio.h>
#include <sys/mman.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
    printf("Caught segfault at address %p\n", si->si_addr);
    mprotect(si->si_addr, sizeof(int), PROT_WRITE);
    printf("\n");
}

int main(void)
{
    //int *foo = NULL;

    int N = 5;
    int *ptr = mmap(NULL, N * sizeof(int), PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

    struct sigaction sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGSEGV, &sa, NULL);

    for (int i = 0; i < N; i++)
        ptr[i] = i * 10;

    for (int i = 0; i < N; i++)
        printf("[%d]", ptr[i]);

    printf("\n");

    return 0;
}
