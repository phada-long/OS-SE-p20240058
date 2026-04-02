#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat fileStat;
    char buffer[512];

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == 0) {
            int len = snprintf(buffer, sizeof(buffer),
                               "%-30s %10ld\n",
                               entry->d_name,
                               fileStat.st_size);
            write(1, buffer, len);
        }
    }

    closedir(dir);
    return 0;
}
