#include <Windows.h>

class PEFile
{
private:
    size_t file_size;
    PIMAGE_DOS_HEADER pDOSHeader;
    PIMAGE_NT_HEADERS pNTHeader;
public:
    PEFile();
};