#include <unistd.h>

int main() {
    const char *msg = "Hello, System Call!\n";
    write(1, msg, 21);
    return 0;
}
