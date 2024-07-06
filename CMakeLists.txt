cmake_minimum_required(VERSION 3.28)
project(Memory C)

set(CMAKE_C_STANDARD 23)

add_executable(Memory main.c)




# Find GTK4 package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# Add GTK4 include directories
target_include_directories(Memory PRIVATE ${GTK4_INCLUDE_DIRS})

# Link GTK4 libraries
target_link_libraries(Memory PRIVATE ${GTK4_LIBRARIES})

# Add other compiler options (optional)
add_compile_options(${GTK4_CFLAGS_OTHER})
