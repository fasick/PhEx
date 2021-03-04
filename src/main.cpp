#include <Windows.h>
#include <iostream>
#include "peFile.hpp"


INT main(INT argc, PCHAR argv[], PCHAR env[])
{
    // CHAR notepadPath[] = "C:\\Windows\\system32\\notepad.exe";   <-- can't get handle when in this location
    CHAR notepadPath[] = "C:\\Users\\fasic\\Desktop\\notepad.exe";
    PEFile *pe = NULL;

    std::cout << "before constructor\n";

    pe = new PEFile(notepadPath);

    std::cout << "created object\n";

    

    delete pe;

    std::cout << "after delete" << std::endl;

    return 0;
}
