# CMakeList.txt : projet CMake pour Tank, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

project(tank)
# cls & cmake .. & cmake --build . --config Release
# Définir la version C++ pour CMake
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set variables
set(SOURCE_DIR src)
set(LIBRARIES_DIR libraries)
set(PYTHON_DIR "C:\\Users\\vince\\AppData\\Local\\Programs\\Python\\Python39")
set(PYTHON_INCLUDE_DIR ${PYTHON_DIR}/include)
set(pybind11_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/pybind11)
set(pybind11_INCLUDE_DIR ${pybind11_DIR}/include)

# Ajoutez une source à l'exécutable de ce projet.
# add_executable(tank_exec ${SOURCE_DIR}/main.cpp)

# Ajouter des dossiers
include_directories(${SOURCE_DIR})
include_directories(${PYTHON_INCLUDE_DIR})

# Ajouter la librairie pybind11
add_subdirectory(${pybind11_DIR})
include_directories(${pybind11_INCLUDE_DIR})

# Ajouter les fichiers source
file(GLOB_RECURSE SOURCES  ${SOURCE_DIR}/*.cpp)
add_library(TankLib SHARED ${SOURCES}) # create .dll
# add_library(TankLib STATIC ${SOURCES}) # create .lib

# Ajouter des drapeaux de compilation
target_compile_options(TankLib PRIVATE -Wall)
set_target_properties(TankLib PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(TankLib PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")
set_target_properties(TankLib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

MESSAGE( [Main] " pybind11_INCLUDE_DIRS = ${pybind11_INCLUDE_DIRS}")
MESSAGE( [Main] " pybind11_LIBRARIES = ${pybind11_LIBRARIES}")

pybind11_add_module(tank_module ${SOURCE_DIR}/tank_obj.cpp ${SOURCE_DIR}/template_obj.cpp ${SOURCE_DIR}/template_keys.cpp ${SOURCE_DIR}/utils.cpp ${SOURCE_DIR}/conform_path.cpp ${SOURCE_DIR}/exception.cpp)
# target_link_libraries(tank_module PRIVATE Tank utils Template_keys)
target_link_libraries(TankLib PRIVATE ${PYTHON_DIR}/libs/python39.lib)

MESSAGE( [Main] " pybind11_INCLUDE_DIRS = ${pybind11_INCLUDE_DIRS}")
MESSAGE( [Main] " pybind11_LIBRARIES = ${pybind11_LIBRARIES}")

# PYBIND11_MODULE(module_name, m){ /* bindings */ }

# Définir le nom de la bibliothèque
# set_target_properties(TankLib PROPERTIES OUTPUT_NAME "TankLib")
# set_target_properties(tank_module PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")

# Définir l'emplacement de sortie de la bibliothèque partagée (DLL)

# set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/build")



