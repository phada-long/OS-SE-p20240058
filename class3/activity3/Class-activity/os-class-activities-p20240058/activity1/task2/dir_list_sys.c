#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>    // Allowed strictly for snprintf data conversion

int main() {
    char buffer[512];
    
    DIR *dir = opendir(".");
    if (dir == NULL) {
        const char *err = "Error opening directory\n";
        write(2, err, strlen(err));
        return 1;
    }

    struct dirent *entry;
    struct stat fileStat;

    // Print headers using system write
    const char *header1 = "Filename                       Size (bytes)\n";
    const char *header2 = "------------------------------ ----------\n";
    write(1, header1, strlen(header1));
    write(1, header2, strlen(header2));

    // Loop through entries
    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == 0) {
            // Convert numbers to string buffer, then write
            int len = snprintf(buffer, sizeof(buffer), "%-30s %10ld\n", entry->d_name, fileStat.st_size);
            write(1, buffer, len);
        }
    }

    closedir(dir);
    return 0;
}
