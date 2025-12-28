# CMakeList.txt : projet CMake pour RndZm_yl1, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.
find_package(SDL3 REQUIRED)

add_executable (RndZm_yl1 "RndZm_yl1.cpp" "RndZm_yl1.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RndZm_yl1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
