cmake_minimum_required(VERSION 3.10)

project(MarinaTK VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_LIB src/value.cpp)

add_library(libmtk ${SRC_LIB})

target_include_directories(libmtk PUBLIC include)

# Dependencies
target_include_directories(libmtk PUBLIC deps/glm-aabb/glm-aabb)

find_package(glm REQUIRED)
target_link_libraries(libmtk PUBLIC glm)
