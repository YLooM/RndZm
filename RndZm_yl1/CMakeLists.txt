find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable (RndZm_yl1 "RndZm_yl1.cpp" "RndZm_yl1.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RndZm_yl1 PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(RndZm_yl1 PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)