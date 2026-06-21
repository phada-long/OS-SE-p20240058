#include <fcntl.h>    // open(), O_RDONLY
#include <unistd.h>   // read(), write(), close()

int main() {
    char buffer[256];
    ssize_t bytesRead;

    // 1. Open "output.txt" for reading only
    int fd = open("output.txt", O_RDONLY);
    if (fd < 0) {
        const char *err = "Error opening file for reading\n";
        write(2, err, 31);
        return 1;
    }

    // 2. Read content in a loop and immediately write to terminal (fd 1)
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, bytesRead);
    }

    close(fd);
    return 0;
}
