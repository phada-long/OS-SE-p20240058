#include <fcntl.h>
#include <unistd.h>

int main() {
    char buffer[256];
    int fd = open("output.txt", O_RDONLY);

    int bytes;
    while ((bytes = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, bytes);
    }

    close(fd);
    return 0;
}
