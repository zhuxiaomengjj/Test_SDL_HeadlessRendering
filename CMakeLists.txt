cmake_minimum_required(VERSION 3.1)
project(HeadlessRenderingDemo)

set(CMAKE_CXX_STANDARD 11)

# Add the path to the SDL2 library
# set(SDL2_INCLUDE_DIR /path/to/SDL2/include)
# set(SDL2_LIBRARY_DIR /path/to/SDL2/lib)

# Set the output directory for the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find SDL2 library
find_package(SDL2 CONFIG REQUIRED)

find_package(Stb REQUIRED)

# Include the SDL2 headers
# include_directories(${SDL2_INCLUDE_DIR})

# Add the source files of the project
set(SOURCES
    src/main.cpp
)

# Create the executable
add_executable(HeadlessRenderingDemo ${SOURCES})

target_include_directories(HeadlessRenderingDemo PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(HeadlessRenderingDemo
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    )

