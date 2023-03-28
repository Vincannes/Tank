cmake_minimum_required (VERSION 3.10.3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (tank VERSION 1.0)

# Subdirs in this project
add_subdirectory(src)

# Executable
add_executable(tank src/main.cpp)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
#
# option(GEARLIB_BUILD_TESTS ON)
#
# if(GEARLIB_BUILD_TESTS)
#   add_subdirectory(test)
#   include(CTest)
#   enable_testing()
# endif()
#
# # Subdirs in this project
# add_subdirectory(src)
#
# # Executable
# add_executable (${CMAKE_PROJECT_NAME} src/main.cpp)
#
# # Third party packages
# add_subdirectory(lib)
#
# # Linking
# target_link_libraries(
# 	${CMAKE_PROJECT_NAME}
# 	PRIVATE Adapters Domain argparse
# )