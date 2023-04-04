# CMakeList.txt : projet CMake pour Tank, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

project ("Tank")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (Tank "Tank.cpp" "Tank.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Tank PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
# Spécifiez le chemin vers la bibliothèque YAML-CPP
