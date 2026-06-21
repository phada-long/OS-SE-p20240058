/* winprocess.c — Process creation on Windows using CreateProcess() */
#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    printf("Parent process (PID: %lu) — creating child...\n", GetCurrentProcessId());

    /* Launch mspaint.exe as a child process */
    if (!CreateProcess(
            "C:\\Windows\\System32\\mspaint.exe",  /* Application path */
            NULL,                                  /* Command line arguments */
            NULL,                                  /* Process security attributes */
            NULL,                                  /* Thread security attributes */
            FALSE,                                 /* Inherit handles */
            0,                                     /* Creation flags */
            NULL,                                  /* Environment block */
            NULL,                                  /* Current directory */
            &si,                                   /* Startup info structure */
            &pi                                    /* Process information structure */
        ))
    {
        fprintf(stderr, "CreateProcess failed (error %lu).\n", GetLastError());
        return 1;
    }

    printf("Child process created!\n");
    printf("  Child PID:       %lu\n", pi.dwProcessId);
    printf("  Child Thread ID: %lu\n", pi.dwThreadId);

    printf("Parent: waiting for child (mspaint) to exit...\n");
    printf(">>> Open Task Manager now and take a screenshot! <<<\n");
    printf(">>> Then close mspaint to let this program finish. <<<\n");

    /* Equivalent to waitpid() in Linux */
    WaitForSingleObject(pi.hProcess, INFINITE);

    printf("Parent: child has exited. Cleaning up.\n");

    /* Close tracking handles to avoid resource leaks */
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}