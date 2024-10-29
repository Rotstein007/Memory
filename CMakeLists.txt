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

# Setup für AppImage
set(APPIMAGE_PATH "${CMAKE_BINARY_DIR}/MemoryGame.AppDir")
file(MAKE_DIRECTORY ${APPIMAGE_PATH}/usr/bin)
file(MAKE_DIRECTORY ${APPIMAGE_PATH}/usr/share/applications)
file(MAKE_DIRECTORY ${APPIMAGE_PATH}/usr/share/icons/hicolor/128x128/apps)

# Installiere das ausführbare Ziel
install(TARGETS Memory DESTINATION "${APPIMAGE_PATH}/usr/bin")

# Erstelle die .desktop-Datei
file(WRITE ${APPIMAGE_PATH}/MemoryGame.desktop "[Desktop Entry]
Name=Memory Game
Exec=./usr/bin/Memory
Icon=MemoryGame
Type=Application
Categories=Game;")

# Überprüfe, ob das Icon existiert und kopiere es
if(EXISTS "${CMAKE_SOURCE_DIR}/img/img.png")
    configure_file(${CMAKE_SOURCE_DIR}/img/img.png ${APPIMAGE_PATH}/MemoryGame.png COPYONLY)
else()
    message(WARNING "Icon file 'Memory.png' not found!")
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/AppRun-x86_64")
    configure_file(${CMAKE_SOURCE_DIR}/AppRun-x86_64 ${APPIMAGE_PATH}/AppRun COPYONLY)
else()
    message(WARNING "AppRun-x86_64 not found!")
endif()

add_custom_command(
        TARGET Memory POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/Memory ${APPIMAGE_PATH}/usr/bin/Memory
)

# Erstelle die AppImage
add_custom_command(TARGET Memory POST_BUILD
        COMMAND ARCH=x86_64 appimagetool ${APPIMAGE_PATH} ${CMAKE_BINARY_DIR}/MemoryGame.AppImage
        COMMENT "Creating AppImage")