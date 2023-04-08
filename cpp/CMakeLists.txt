# CMakeList.txt : projet CMake pour Tank, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

project(tank)
# cls & cmake .. & cmake --build .
# Définir la version C++ pour CMake
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set variables
set(SOURCE_DIR src)
set(LIBRARIES_DIR libraries)
set(PYTHON_DIR "C:\\Users\\vince\\AppData\\Local\\Programs\\Python\\Python39")
set(PYTHON_INCLUDE_DIR ${PYTHON_DIR}/include)

# Ajoutez une source à l'exécutable de ce projet.
# add_executable(tank_exec ${SOURCE_DIR}/main.cpp)

file(GLOB_RECURSE SOURCES_H  ${SOURCE_DIR}/*.h)
file(GLOB_RECURSE SOURCES_CPP ${SOURCE_DIR}/*.cpp)

# Liste des fichiers .cpp à compiler
set(SOURCES SOURCES_CPP)

# Liste des fichiers .h
set(HEADERS SOURCES_H)

# Définition de la bibliothèque partagée
add_library(${PROJECT_NAME} SHARED ${SOURCES_CPP})

# Ajout des répertoires d'inclusion
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Options de compilation pour la DLL
set_target_properties(${PROJECT_NAME} PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS TRUE
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN TRUE
)

# Installation de la bibliothèque partagée
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/src
)
install(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/src
)
