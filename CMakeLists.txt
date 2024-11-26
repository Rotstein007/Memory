cmake_minimum_required(VERSION 3.28)
project(Memory CXX)

set(CMAKE_CXX_STANDARD 23)

# Add all source and header files
set(SOURCES
        main.cpp
        LinkedList.cpp
        MemorySpiel.cpp
)

set(HEADERS
        LinkedList.h
        MemorySpiel.h
)

# Create the executable target
add_executable(Memory ${SOURCES} ${HEADERS})

# Find the GTK4 package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# Add the GTK4 include directories
target_include_directories(Memory PRIVATE ${GTK4_INCLUDE_DIRS})

# Link the GTK4 libraries
target_link_libraries(Memory PRIVATE ${GTK4_LIBRARIES})

# Add other compiler options (optional)
target_compile_options(Memory PRIVATE ${GTK4_CFLAGS_OTHER})