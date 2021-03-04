

project( peFile )

# add_library( ${PROJECT_NAME} peFile.cpp peFile.hpp )

target_sources( main PRIVATE peFile.cpp )
target_include_directories( main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )

# Find the ShLwApi | needed for PathFileExistsW()
# TODO: is there a better way to find this library?
#           maybe set a var with all windows libraries?
#           maybe set CMAKE_LIBRARY_PATH?
find_library( Shlwapi_LIBRARY_PATH
              NAMES ShLwApi ShLwApi.lib shlwapi shlwapi.lib
              HINTS "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\SDK\\ScopeCppSDK\\vc15\\SDK\\lib" )
target_link_libraries( main ${Shlwapi_LIBRARY_PATH} )
