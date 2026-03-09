cmake_minimum_required(VERSION 3.20)
project(SolarSystem)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
  matplot
  GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus.git
  GIT_TAG master
)

FetchContent_MakeAvailable(matplot)

add_executable(solar the_solar_system.cpp)

target_link_libraries(solar PUBLIC matplot)
