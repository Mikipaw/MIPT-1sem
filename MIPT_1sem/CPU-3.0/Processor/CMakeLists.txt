cmake_minimum_required(VERSION 3.16)
project(Processor)

set(CMAKE_CXX_STANDARD 20)

add_executable(Processor main.cpp CPU.cpp)
target_include_directories(Processor PUBLIC C:\\Programming\\projects\\onegin2)
target_include_directories(Processor PUBLIC C:\\Programming\\projects\\CPU2\\Common)

find_library(ONEGIN_LIBRARY objects lib)
target_link_libraries(Processor LINK_PUBLIC ${ONEGIN_LIBRARY} -lOpenGL32 -lfreeGLUT)