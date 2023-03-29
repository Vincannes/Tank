cmake_minimum_required (VERSION 3.10.3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (tank VERSION 1.0)

find_package(RapidJSON)

add_executable(test
  main.cpp)

  target_include_directories(test
  PUBLIC
  ${PARENT_DIR_INSTALL_PREFIX}/YAML_CPP/include >
  )

target_link_libraries(test debug yaml-cppd optimized yaml-cpp)
#

# Subdirs in this project
add_subdirectory(src)

# Executable
add_executable(tank src/main.cpp)

# Ajouter la bibliothèque yaml-cpp à votre projet
target_link_libraries(MyExecutable yaml-cpp)