# # Specify the minimum version of CMake required
# cmake_minimum_required(VERSION 3.10)

# # Set the project name and version
# project(MyProject VERSION 1.0 LANGUAGES CXX)

# # Set the C++ standard to C++11 (or any other version you need)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# # Add include directory
# include_directories(${PROJECT_SOURCE_DIR}/include)

# # Add source files
# file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# # Create the executable
# add_executable(warden ${SOURCES})


# # Optionally, link libraries if needed
# target_link_libraries(warden fmt)


# # Specify where the executable will be installed
# install(TARGETS warden DESTINATION bin)

# # Install header files
# install(DIRECTORY include/ DESTINATION include)

# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyProject VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard to C++17 (or any other version you need)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Create the executable
add_executable(warden ${SOURCES})

# Specify where the executable will be installed
install(TARGETS warden DESTINATION bin)

# Install header files
install(DIRECTORY include/ DESTINATION include)

# Define installation rules for different platforms
if(WIN32)
    # Install the application for Windows
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")
    install(CODE "message(\"Installing on Windows: Executable will be in ${CMAKE_INSTALL_PREFIX}/bin\")")
    # You might want to adjust PATH environment variable or use CPack to create an installer
else()
    # Default install prefix for Unix-like systems
    install(CODE "message(\"Installing on Unix-like OS: Executable will be in /usr/local/bin\")")
endif()
