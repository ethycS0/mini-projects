#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

int main(void) {
    HMODULE mainDLL = NULL;
    wchar_t dllPATH[MAX_PATH] = L"C:\\Users\\main\\Documents\\malware-creation-and-analysis\\process-injection\\DLL-injection\\dll\\x64\\Debug\\process.dll";
    printf("\n Trying to get a Handle to %s", dllPATH);
    mainDLL = LoadLibraryW(dllPATH);

    if(mainDLL == NULL){
        printf("\n Could not get a Handle to process.dll, error: 0x%lx", GetLastError());
        return EXIT_FAILURE;
    }
    printf("\n Got a Handle to process.dll");
    printf("---0x%p", mainDLL);

    printf("\n Freeing the module");
    FreeLibrary(mainDLL);
    printf("\n Finished. Press any key to exit.");
    getchar();

    return EXIT_SUCCESS;
}