# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyProject VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard to C++11 (or any other version you need)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Create the executable
add_executable(warden ${SOURCES})

# Optionally, link libraries if needed
target_link_libraries(warden fmt)
