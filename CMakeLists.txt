cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(MyApp src/main.cpp src/MyClass.cpp)

# Optionally, you can include headers if needed
target_include_directories(MyApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
