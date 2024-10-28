#include <stdio.h>
#include <windows.h>

int main(void) {

    STARTUPINFOW si = {0};
    PROCESS_INFORMATION pi = {0};

    if(!CreateProcessW(
        L"C:\\Windows\\System32\\notepad.exe",
        NULL,
        NULL,
        NULL,
        FALSE,
        NORMAL_PRIORITY_CLASS,
        NULL,
        NULL,
        &si,
        &pi
    ))
    {
        printf("\n Failed to create Process: %ld", GetLastError);
        return EXIT_FAILURE;
    }
    else {
        printf("\n Process started successfully");
        printf("\n PID: %ld", pi.dwProcessId);
        printf("\n TID: %ld", pi.dwThreadId);
        printf("\n Handles Process: 0x%x", pi.hProcess);
        printf("\n Handles Thread: 0x%x", pi.hThread);
    }

    WaitForSingleObject(
        pi.hProcess,
        INFINITE
    );

    printf("\n finished! exiting...");

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return EXIT_SUCCESS;
}