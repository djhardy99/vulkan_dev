# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.28.3)

# Define the project name and version
project(VulkanDev VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the directories for includes (if any, for future scalability)
include_directories(${PROJECT_SOURCE_DIR}/include)

# Recursively find all source files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the executable target
add_executable(app.exe ${SOURCES})

# Optionally, specify the output directories for the binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Add compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2")

# Add linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi")

# Specify the libraries to link against
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

# Link libraries to your target
target_link_libraries(app.exe Vulkan::Vulkan glfw)
