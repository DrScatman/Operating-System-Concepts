#include <unistd.h>

int main() {
    // The list of args must end with a NULL
    execl("/usr/bin/cal", "some random string", "-3", "2045", NULL);
    perror("After exec()");
    printf ("Just checking\n");
    return 0;
}