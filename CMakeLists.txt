cmake_minimum_required(VERSION 3.16)

project(color CXX)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(fetch/OpenCV)

# set(OpenCV_DIR "C:/Users/10272/Downloads/opencv-4.5.5-vc14_vc15/opencv/x64/vc15/lib")

# find_package(OpenCV REQUIRED)
# link_libraries( ${OpenCV_LIBS} )

add_subdirectory(lib)
add_subdirectory(app)




