cmake_minimum_required(VERSION 3.16)
project(3d_line_plane_intersection LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(orocos_kdl REQUIRED)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

include_directories(${orocos_kdl_INCLUDE_DIRS})

include_directories(
    include
)

add_executable(3d_line_plane_intersection
    src/test.cpp
    src/3dlineplaneintersection.cpp
    include/3dlineplaneintersection.h
)

set_target_properties(3d_line_plane_intersection PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

# target_link_libraries(3d_line_plane_intersection PUBLIC
#     gtest
#     gtest_main
#     ${orocos_kdl_LIBRARIES}
# )

target_link_libraries(3d_line_plane_intersection 
    ${GTEST_LIBRARIES}
    pthread #need to put it after GTEST. Linker takes them in order
    ${orocos_kdl_LIBRARIES}
)