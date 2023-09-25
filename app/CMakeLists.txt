cmake_minimum_required(VERSION 3.16)

project(app_test CXX)

add_executable(${PROJECT_NAME} test.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC 
${VISION_INCLUDE_DIRS}
)
message(".......... " ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} PUBLIC 
ColorCorrection
${OpenCV_LIBS}
)

install(TARGETS ${PROJECT_NAME} 
		BUNDLE DESTINATION .)














