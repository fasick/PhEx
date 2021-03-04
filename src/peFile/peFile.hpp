#include <Windows.h>

class PEFile
{
private:
    SIZE_T cbFile;
    PBYTE pFileContents;
    PWCHAR pwcFilePath;
    HANDLE hFile;
    PIMAGE_DOS_HEADER pDOSHeader;
    PIMAGE_NT_HEADERS pNTHeader;
    PIMAGE_FILE_HEADER pFileHeader;
    PIMAGE_OPTIONAL_HEADER pOptHeader;

    VOID init(_In_ PWCHAR pwcFilePath);

public:
    // constructos & destructor
    PEFile(_In_ PCHAR pcFilePath);
    PEFile(_In_ PWCHAR pwcFilePath);
    ~PEFile(VOID);

    // getters/setters
    HRESULT getDOSHeader(_Out_ PIMAGE_DOS_HEADER pDOSHeader);
    HRESULT setDOSHeader(VOID);

};