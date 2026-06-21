#include <fcntl.h>    // open(), O_WRONLY, O_CREAT, O_TRUNC
#include <unistd.h>   // write(), close()
#include <string.h>   // strlen()

int main() {
    // 1. Open/create "output.txt" with standard flags
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        const char *err = "Error opening file\n";
        write(2, err, strlen(err)); // fd 2 = stderr
        return 1;
    }

    // 2. Write the required message
    const char *text = "Hello from Operating Systems class!\n";
    write(fd, text, strlen(text));

    // 3. Close file descriptor
    close(fd);

    // 4. Print confirmation to terminal (fd 1 = stdout)
    const char *success_msg = "File created successfully!\n";
    write(1, success_msg, strlen(success_msg));

    return 0;
}
