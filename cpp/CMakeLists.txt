# CMakeList.txt : projet CMake pour Tank, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

project(tank)

# Ajoutez une source à l'exécutable de ce projet.
add_executable (tank "main_tank.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Tank PROPERTY CXX_STANDARD 20)
endif()

set(SOURCE_DIR src)
set(LIBRARIES_DIR libraries)

include_directory(${SOURCE_DIR})
add_subdirectory(${LIBRARIES_DIR})
add_subdirectory(pybind11)

add_library(Tank ${SOURCE_DIR}/Tank.cpp)
add_library(utils ${SOURCE_DIR}/utils.cpp)
add_library(ConformPath ${SOURCE_DIR}/conform_path.cpp)
add_library(Template_keys ${SOURCE_DIR}/template_keys.cpp)
add_library(Template_obj ${SOURCE_DIR}/template_obj.cpp)
add_library(Templates_obj ${SOURCE_DIR}/templates_obj.cpp)

set_target_properties(Tank PROPERTIES POSITION_INDEPENDENT_CODE ON)

pybind11_add_module(tank ${SOURCE_DIR}/main_tank.cpp)

# set(HELLO_SOURCES ${SOURCE_DIR}hello.cpp ${SOURCE_DIR}autre.cpp)
# add_librairy(toto ${HELLO_SOURCES})
# add_executable(Hello  apps/main.cpp)
# target_link_librairies(Hello toto)

