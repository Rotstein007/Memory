cmake_minimum_required(VERSION 3.28)
project(Memory CXX)

set(CMAKE_CXX_STANDARD 23)

# Füge alle Quell- und Header-Dateien hinzu
set(SOURCES
        main.cpp
        LinkedList.cpp
        MemorySpiel.cpp
)

set(HEADERS
        LinkedList.h
        MemorySpiel.h
)

# Erstelle das ausführbare Ziel
add_executable(Memory ${SOURCES} ${HEADERS})

# Finde das GTK4-Paket
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# Füge die GTK4 Include-Verzeichnisse hinzu
target_include_directories(Memory PRIVATE ${GTK4_INCLUDE_DIRS})

# Verlinke die GTK4-Bibliotheken
target_link_libraries(Memory PRIVATE ${GTK4_LIBRARIES})

# Füge andere Compiler-Optionen hinzu (optional)
add_compile_options(${GTK4_CFLAGS_OTHER})