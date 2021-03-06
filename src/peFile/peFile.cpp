#include "peFile.hpp"
#include <iostream>
#include <Windows.h>
#include <Shlwapi.h>



// constructos & destructor
PEFile::PEFile(_In_ PCHAR pcFilePath):
    cbFile(INVALID_FILE_SIZE),
    pFileContents(NULL),
    pwcFilePath(NULL),
    hFile(INVALID_HANDLE_VALUE),
    pDOSHeader(NULL),
    pNTHeader(NULL),
    pFileHeader(NULL),
    pOptHeader(NULL)
{
    SIZE_T cbFilePath = 0;

    std::cout <<"in PEFile(PCHAR)\n";

    // Check to see if we were passed a NULL ptr
    if(!pcFilePath)
    {
        std::cerr << "pcFilePath is NULL\n";
        throw std::invalid_argument("pcFilePath must not be NULL.");
    }

    // Find out how much memory we need to request for the wchar
    cbFilePath =  MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pcFilePath, strlen(pcFilePath)+1, NULL, 0);

    std::cout << "bytes needed for wchar: " << cbFilePath << '\n';

    this->pwcFilePath = (PWCHAR)VirtualAlloc(NULL, cbFilePath, MEM_COMMIT, PAGE_READWRITE);
    if(!this->pwcFilePath)
    {
        std::cerr << "malloc failed\n";
        throw std::exception("Error allocating new memory. Could not create PE file object.");
    }

    if(!MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pcFilePath, strlen(pcFilePath)+1, this->pwcFilePath, cbFilePath))
    {
        std::cout << "Error" << '\n';
    }

    // Attempt to initialize the PE file object
    try
    {
        PEFile::init(pwcFilePath);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error initializng the PE file object." << '\n';
        std::cerr << e.what() << '\n';
        // TODO: either throw another exception, or try init again
    }
}

PEFile::PEFile(_In_ PWCHAR pwcFilePath):
    cbFile(INVALID_FILE_SIZE),
    pFileContents(NULL),
    pwcFilePath(NULL),
    hFile(INVALID_HANDLE_VALUE),
    pDOSHeader(NULL),
    pNTHeader(NULL),
    pFileHeader(NULL),
    pOptHeader(NULL)
{
    // Check to see if we were passed a NULL ptr
    if(!pwcFilePath)
    {
        throw std::invalid_argument("pwcFilePath must not be NULL.");
    }

    // Attempt to initialize the PE file object
    try
    {
        PEFile::init(pwcFilePath);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error initializng the PE file object." << '\n';
        std::cerr << e.what() << '\n';
        // TODO: either throw another exception, or try init again
    }
}

VOID PEFile::init(_In_ PWCHAR pwcFilePath)
{
    SIZE_T cbBytesRead = 0;

    // check if file exists
    if(!PathFileExistsW((LPCWSTR)pwcFilePath))
    {
        std::cout << "path doesn't exist\n";
        throw std::invalid_argument("Can't find file.\n");
    }

    // createfile
    this->hFile = CreateFileW(pwcFilePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(this->hFile == INVALID_HANDLE_VALUE)
    {
        // todo: call GetLastError
        printf("Failed to get file handle %#x\n", GetLastError());
        throw std::exception("Failed to get file handle.\n");
    }

    // getfilesize
    this->cbFile = GetFileSize(this->hFile, NULL);
    if(this->cbFile == INVALID_FILE_SIZE)
    {
        std::cerr << "Failed to get file size.\n";
        throw std::exception("Failed to get file size.\n");
    }

    // virtualalloc
    this->pFileContents = (PBYTE)VirtualAlloc(NULL, this->cbFile, MEM_COMMIT, PAGE_READWRITE);
    if(!this->pFileContents)
    {
        std::cerr << "Failed to alloc memory for file.\n";
        throw std::exception("Failed to alloc memory for file.\n");
    }

    // readfile
    if(!ReadFile(this->hFile, this->pFileContents, this->cbFile, (LPDWORD)&cbBytesRead, NULL))
    {
        std::cerr << "Failed to read file contents.\n";
        throw std::exception("Failed to read file contents.\n");
    }

    // setup the rest of our pointers
    this->pDOSHeader = (PIMAGE_DOS_HEADER)this->pFileContents;
    this->pNTHeader = (PIMAGE_NT_HEADERS)((PBYTE)this->pDOSHeader + (DWORD)this->pDOSHeader->e_lfanew);
    this->pFileHeader = (PIMAGE_FILE_HEADER)(&this->pNTHeader->FileHeader);
    this->pOptHeader = (PIMAGE_OPTIONAL_HEADER)(&this->pNTHeader->OptionalHeader);
    
#ifdef VERBOSE
    printf("First byte of data from notepad.exe: %#x\n", *(this->pFileContents));
    printf("address of pDOSHeader: %p\n", this->pDOSHeader);
    printf("pDOSHeader->e_lfanew: %#x\n", (this->pDOSHeader->e_lfanew));
    printf("address of pNTHeader: %p\n", this->pNTHeader);
    printf("first byte of NTHeader: %#x\n", *(PBYTE)(this->pNTHeader));
    printf("address of pFileHeader: %p\n", this->pFileHeader);
    printf("first byte of fileHeader: 0x%04x\n", *(PSHORT)(this->pFileHeader));
    printf("address of pOptHeader: %p\n", this->pOptHeader);
    printf("first byte of OptHeader: 0x%04x\n", *(PSHORT)(this->pOptHeader));
#endif
}

PEFile::~PEFile(VOID)
{
    if(this->pwcFilePath)
    {
        VirtualFree(this->pwcFilePath, 0, MEM_RELEASE);
        this->pwcFilePath = NULL;
    }

    if(this->hFile != INVALID_HANDLE_VALUE)
    {
        CloseHandle(this->hFile);
        this->hFile = INVALID_HANDLE_VALUE;
    }

    if(this->pFileContents)
    {
        VirtualFree(this->pFileContents, 0, MEM_RELEASE);
        this->pFileContents = NULL;
    }
}

// getters/setters
HRESULT PEFile::getDOSHeader(_Out_ PIMAGE_DOS_HEADER pDOSHeader)
{
    HRESULT hresult = S_OK;

    return hresult;
}
HRESULT PEFile::setDOSHeader(VOID)
{
    HRESULT hresult = S_OK;

    return hresult;
}