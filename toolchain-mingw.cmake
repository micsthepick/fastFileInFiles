# Set the target architecture by passing -DTARGET_ARCH=i386 or -DTARGET_ARCH=x86_64
set(TARGET_ARCH x86_64 CACHE STRING "Target architecture ('i386' or 'x86_64')")

if(TARGET_ARCH STREQUAL "x86_32")
    set(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
    set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
    set(CMAKE_RC_COMPILER i686-w64-mingw32-windres)
    set(CMAKE_FIND_ROOT_PATH /usr/i686-w64-mingw32)
elseif(TARGET_ARCH STREQUAL "x86_64")
    set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
    set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
    set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)
    set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)
else()
    message(FATAL_ERROR "Unsupported TARGET_ARCH: ${TARGET_ARCH}")
endif()

# Specify that we're cross-compiling
set(CMAKE_SYSTEM_NAME Windows)

# Prevent CMake from testing the cross-compiler's executable output, which won't run natively
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
