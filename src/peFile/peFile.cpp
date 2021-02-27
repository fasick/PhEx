#include "peFile.hpp"
#include <iostream>


// constructos & destructor
PEFile::PEFile(_In_ PCHAR pcFilePath)
{
    SIZE_T cbFilePath = 0;

    cbFilePath =  MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pcFilePath, strlen(pcFilePath)+1, NULL, 0);

    this->pwcFilePath = (PWCHAR)malloc(cbFilePath);
    if(!this->pwcFilePath)
    {
        // error
        std::cout << "Error" << std::endl;
    }

    if(!MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pcFilePath, strlen(pcFilePath)+1, this->pwcFilePath, cbFilePath))
    {
        std::cout << "Error" << std::endl;
    }

    PEFile::init(this->pwcFilePath);
}

PEFile::PEFile(_In_ PWCHAR pwcFilePath)
{

}

VOID PEFile::init(_In_ PWCHAR pwcFilePath)
{

}

PEFile::~PEFile(VOID)
{

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