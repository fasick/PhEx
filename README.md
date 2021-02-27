# **PhEx**

The objective of this project is to create a hex editor for
PE files. The PE (portable executable) file format is used
for exe files, dlls, and others (see the wiki https://en.wikipedia.org/wiki/Portable_Executable)

## Current Project Planning
### PE File Class
Create a C++ class to represent the PE File format. Allow users to
examine the different sections of the PE file.
### Boost.Python Wrapper
Use Boost.Python to wrap the PEFile class and expose
the API to python.
### Python Qt
Use Qt python to create a hex editor GUI to inspect the PE file.
### Enable Editing
Update the C++ PEFile class to allow a user to edit the file.
