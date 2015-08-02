#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

int main() {
    struct rlimit lim;
    getrlimit(RLIMIT_STACK, &lim);
    printf("stack size: %lu\n", (long unsigned int)lim.rlim_cur/1024);
    
    getrlimit(RLIMIT_NPROC, &lim);
    printf("process limit: %lu\n", (long unsigned int)lim.rlim_cur);
    
    getrlimit(RLIMIT_NOFILE, &lim);
    printf("max file descriptors: %lu\n", (long unsigned int)lim.rlim_cur);
}
