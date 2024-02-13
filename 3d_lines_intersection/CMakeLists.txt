cmake_minimum_required(VERSION 3.16)
project(3d_lines_intersection LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)

# Set the path to the Qt53DExtrasConfig.cmake file
set(Qt6_DIR "/usr/local/Qt-6.5.2/lib/cmake/Qt6")

find_package(Qt6 REQUIRED COMPONENTS 3DCore 3DExtras 3DInput 3DRender Core Gui Widgets)

find_package(orocos_kdl REQUIRED)

include_directories(${orocos_kdl_INCLUDE_DIRS})

include_directories(include)

qt_add_executable(3d_lines_intersection
    src/main.cpp
    src/drawline.cpp 
    include/drawline.h
    src/3dlinesintersection.cpp 
    include/3dlinesintersection.h
    src/drawsphere.cpp 
    include/drawsphere.h
)

qt_add_executable(3d_lines_intersection_test
    src/test.cpp
    src/3dlinesintersection.cpp 
    include/3dlinesintersection.h
)

set_target_properties(3d_lines_intersection PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(3d_lines_intersection PUBLIC
    Qt::3DCore
    Qt::3DExtras
    Qt::3DInput
    Qt::3DRender
    Qt::Core
    Qt::Gui
    Qt::Widgets
    ${orocos_kdl_LIBRARIES}
)

target_link_libraries(3d_lines_intersection_test PUBLIC
    gtest
    gtest_main
    ${orocos_kdl_LIBRARIES}
    )