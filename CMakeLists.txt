cmake_minimum_required(VERSION 3.10)
project(LiveOceanSimulation)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(ocean
    src/main.cpp
    src/entity.cpp
    src/ocean.cpp
    src/algae.cpp
    src/herbivore.cpp
    src/predator.cpp
)

target_link_libraries(ocean pdcurses)