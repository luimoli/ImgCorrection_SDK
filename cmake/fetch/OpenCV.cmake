include(FetchContent)
if(NOT Opencv_Found)

if(NOT DEFINED OpenCV_URL)
if(WIN32)
    set(OpenCV_URL "https://devops-generic.pkg.coding.smoa.cloud/vix3d/projects/opencv-4.5.5-vc14_vc15.zip?version=latest")
else()
    message(FATEL_ERROR "Need Opencv4.5-linux package.")
endif()
endif()

FetchContent_Declare(OpenCV
    URL ${OpenCV_URL}
    SOURCE_DIR ${VGA_THIRDPARTY_DIR}/opencv
)
message(STATUS "Fetching opencv : ${OpenCV_URL}")
FetchContent_MakeAvailable(OpenCV)
message(STATUS "Fetching done")

FetchContent_GetProperties(OpenCV SOURCE_DIR OpenCV_SOURCE_DIR)
message(STATUS "OpenCV src dir : ${OpenCV_SOURCE_DIR}")
# get OpenCV_DIR
if(WIN32)
    set(OpenCV_DIR ${OpenCV_SOURCE_DIR}/x64/vc15/lib)
else()
    set(OpenCV_DIR ${OpenCV_SOURCE_DIR}/lib/cmake/opencv4)
endif()

endif()

set(OpenCV_INCLUDE ${OpenCV_SOURCE_DIR}/include)

if(WIN32)
    file(GLOB_RECURSE OpenCV_BIN "${OpenCV_SOURCE_DIR}/bin/*.dll")
else ()
    file(GLOB_RECURSE OpenCV_BIN "${OpenCV_SOURCE_DIR}/bin/*.so")
endif()

find_package(OpenCV REQUIRED)