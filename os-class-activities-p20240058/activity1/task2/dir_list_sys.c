#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

int main() {
    char buffer[512];
    int len;

    // 1. Open current directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        write(2, "Error opening directory\n", 24);
        return 1;
    }

    // 2. Print header using write()
    const char *header1 = "Filename                           Size (bytes)\n";
    const char *header2 = "------------------------------     ----------\n";
    write(1, header1, strlen(header1));
    write(1, header2, strlen(header2));

    // 3. Loop through entries
    struct dirent *entry;
    struct stat fileStat;

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == 0) {
            // 4. Format into buffer then write()
            len = snprintf(buffer, sizeof(buffer),
                           "%-30s %10ld\n",
                           entry->d_name, fileStat.st_size);
            write(1, buffer, len);
        }
    }

    // 5. Close directory
    closedir(dir);
    return 0;
}
