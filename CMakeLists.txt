cmake_minimum_required(VERSION 3.10)
project(FastFindInFiles)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Specify the MinGW toolchain file
set(CMAKE_TOOLCHAIN_FILE "/usr/share/mingw-w64/toolchain.cmake")

# Add all your source files
set(SOURCES 
    src/DockingFeature/GoToLineDlg.cpp
    src/DockingFeature/StaticDialog.cpp
    src/fff.cpp
    src/FastFindInFiles.cpp
    src/PluginDefinition.cpp
)

# Add all your header files
set(HEADERS 
    src/DockingFeature/Docking.h
    src/DockingFeature/DockingDlgInterface.h
    src/DockingFeature/dockingResource.h
    src/DockingFeature/GoToLineDlg.h
    src/DockingFeature/resource.h
    src/DockingFeature/StaticDialog.h
    src/DockingFeature/Window.h
    src/fff.h
    src/menuCmdID.h
    src/Notepad_plus_msgs.h
    src/PluginDefinition.h
    src/PluginInterface.h
    src/Scintilla.h
    src/Sci_Position.h
)

# Create a shared library (DLL) from your sources
add_library(FastFindInFiles SHARED ${SOURCES} ${HEADERS})

target_compile_definitions(FastFindInFiles PRIVATE UNICODE _UNICODE WIN32 _DEBUG _WINDOWS _USRDLL NPPPLUGINTEMPLATE_EXPORTS _CRT_NONSTDC_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _CRT_NON_CONFORMING_SWPRINTFS=1)

# Set the output directory for the DLL
set_target_properties(FastFindInFiles PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)