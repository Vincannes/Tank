# CMakeList.txt : projet CMake pour Tank, incluez la source et définissez
# la logique spécifique au projet ici.
# cmake -DCMAKE_C_COMPILER="C:/mingw64/bin/gcc.exe" -DCMAKE_CXX_COMPILER="C:/mingw64/bin/g++.exe" -G "MinGW Makefiles" .. & cmake --build . --config Release 

cmake_minimum_required (VERSION 3.8)

project(tank)
# Définir la version C++ pour CMake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Utiliser MinGW comme compilateur
set(CMAKE_C_COMPILER "C:/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/mingw64/bin/g++.exe")

# Set variables
set(SOURCE_DIR src)
set(LIBRARIES_DIR libraries)
set(PYTHON_DIR "C:/Users/User/AppData/Local/Programs/Python/Python37")
set(Python_DIR ${PYTHON_DIR})
set(PYTHON_INCLUDE_DIR ${PYTHON_DIR}/include)
set(PYTHON_LIBRARIES ${PYTHON_DIR}/libs/python37.lib)
set(pybind11_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/pybind11)
set(pybind11_INCLUDE_DIR ${pybind11_DIR}/include)
set(YAML_CPP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/yaml-cpp)
set(YAML_CPP_INCLUDE_DIR ${YAML_CPP_DIR}/include)

list(APPEND CMAKE_PREFIX_PATH ${YAML_CPP_DIR}/build)
list(APPEND CMAKE_PREFIX_PATH ${PYTHON_DIR}/python.exe)

# Ajouter des dossiers
find_package(Python COMPONENTS Interpreter Development PATHS ${PYTHON_DIR})
include_directories(${SOURCE_DIR})
include_directories(${PYTHON_INCLUDE_DIR})
link_directories(${PYTHON_DIR}/libs/)

# Ajouter la librairie pybind11
add_subdirectory(${pybind11_DIR})
include_directories(${pybind11_INCLUDE_DIR})

# Ajouter la librairie yaml_cpp
add_subdirectory(${YAML_CPP_DIR})
include_directories(${YAML_CPP_DIR}/include)
include_directories(${YAML_CPP_DIR}/include/yaml-cpp)
link_directories(${YAML_CPP_DIR}/build)

# Ajouter les fichiers source
file(GLOB_RECURSE SOURCES  ${SOURCE_DIR}/*.cpp)
add_library(TankLib SHARED ${SOURCES}) # create .dll
# add_library(TankLib STATIC ${SOURCES}) # create .lib

# Ajouter des drapeaux de compilation
target_compile_options(TankLib PRIVATE -Wall)
set_target_properties(TankLib PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(TankLib PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")
set_target_properties(TankLib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")
target_link_libraries(TankLib PRIVATE yaml-cpp)

message(" ")
message("Prefix paths: ${CMAKE_PREFIX_PATH}")
message("    pybind11_INCLUDE_DIRS = ${pybind11_INCLUDE_DIR}")
message("    pybind11_LIBRARIES = ${pybind11_LIBRARIES}")
message("PYTHON_LIBRARIES: ${PYTHON_LIBRARIES}")
message(" ")

# pybind11_add_module(tank_module ${SOURCE_DIR}/tank_obj.cpp ${SOURCE_DIR}/template_obj.cpp ${SOURCE_DIR}/template_keys.cpp ${SOURCE_DIR}/utils.cpp ${SOURCE_DIR}/conform_path.cpp ${SOURCE_DIR}/exception.cpp)
# target_link_libraries(tank_module PRIVATE yaml-cpp ${PYTHON_LIBRARIES})
# target_link_libraries(tank_module PRIVATE yaml-cpp "C:/Users/User/AppData/Local/Programs/Python/Python37/libs/python37.lib")
# target_link_libraries(TankLib PRIVATE yaml-cpp "C:/Users/User/AppData/Local/Programs/Python/Python37/libs/python37.lib")

pybind11_add_module(tank_module ${SOURCE_DIR}/tank_obj.cpp ${SOURCE_DIR}/template_obj.cpp ${SOURCE_DIR}/template_keys.cpp ${SOURCE_DIR}/utils.cpp ${SOURCE_DIR}/conform_path.cpp ${SOURCE_DIR}/exception.cpp)
target_link_libraries(tank_module PRIVATE yaml-cpp "C:/Users/User/AppData/Local/Programs/Python/Python37/libs/python37.lib")
target_link_libraries(TankLib PRIVATE yaml-cpp "C:/Users/User/AppData/Local/Programs/Python/Python37/libs/python37.lib")
