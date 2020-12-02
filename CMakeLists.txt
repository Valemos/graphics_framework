cmake_minimum_required(VERSION 3.17)
project(GraphicalFramework)

set(CMAKE_CXX_STANDARD 14)

include_directories(D:/coding/cpp_libs/GLM)
include_directories(D:/coding/cpp_libs/GLEW/include)
include_directories(D:/coding/cpp_libs/GLFW/include)
include_directories(Framework/framework)
include_directories(Framework/framework/2d_objects)
include_directories(Framework/framework/basic_3d_objects)
include_directories(Framework/framework/draw_objects)
include_directories(Programs/programs_source)
include_directories(Programs/programs_source/gravity_simulation)
include_directories(Programs/programs_source/gravity_simulation/objects)
include_directories(Programs/programs_source/gravity_simulation/vector_editor)
include_directories(Vector/source)

add_library(GraphicalFramework
        Framework/framework/2d_objects/Grid2D.cpp
        Framework/framework/2d_objects/Grid2D.h
        Framework/framework/basic_3d_objects/AxisObject.h
        Framework/framework/basic_3d_objects/Cube.h
        Framework/framework/basic_3d_objects/Dodecahedron.h
        Framework/framework/basic_3d_objects/Sphere.h
        Framework/framework/basic_3d_objects/Surface.h
        Framework/framework/draw_objects/Camera.cpp
        Framework/framework/draw_objects/Camera.h
        Framework/framework/draw_objects/Drawable.cpp
        Framework/framework/draw_objects/Drawable.h
        Framework/framework/draw_objects/Figure2D.cpp
        Framework/framework/draw_objects/Figure2D.h
        Framework/framework/draw_objects/Line.cpp
        Framework/framework/draw_objects/Line.h
        Framework/framework/draw_objects/Object3D.cpp
        Framework/framework/draw_objects/Object3D.h
        Framework/framework/draw_objects/Primitive.cpp
        Framework/framework/draw_objects/Primitive.h
        Framework/framework/draw_objects/Quad.cpp
        Framework/framework/draw_objects/Quad.h
        Framework/framework/draw_objects/Triangle.cpp
        Framework/framework/draw_objects/Triangle.h
        Framework/framework/draw_objects/TriangleFan.cpp
        Framework/framework/draw_objects/TriangleFan.h
        Framework/framework/ButtonHandler.cpp
        Framework/framework/ButtonHandler.h
        Framework/framework/Program.h
        Framework/framework/ProgramInputHandler.cpp
        Framework/framework/ProgramInputHandler.h
        Framework/framework/Renderer.cpp
        Framework/framework/Renderer.h
        Vector/source/Vector3.cpp
        Vector/source/Vector3.h)


add_definitions(-DGLEW_STATIC)
target_link_libraries(GraphicalFramework opengl32.lib)
target_link_libraries(GraphicalFramework D:/coding/cpp_libs/GLEW/lib/Release/Win32/glew32s.lib)
target_link_libraries(GraphicalFramework D:/coding/cpp_libs/GLFW/lib-vc2019/glfw3.lib)


add_executable(Programs
        Programs/programs_source/GridVisualization.cpp
        Programs/programs_source/GridVisualization.h
        Programs/programs_source/ProgramMultipleObjects.cpp
        Programs/programs_source/ProgramMultipleObjects.h
        Programs/programs_source/SpaceMetricGrid.cpp
        Programs/programs_source/SpaceMetricGrid.h
        Programs/programs_source/Test2DObject.h
        Programs/programs_source/Test3DObject.h
        Programs/main.cpp)

target_link_libraries(Programs GraphicalFramework)

add_executable(GravitySimulation
        Programs/programs_source/gravity_simulation/objects/CelestialBody.cpp
        Programs/programs_source/gravity_simulation/objects/CelestialBody.h
        Programs/programs_source/gravity_simulation/objects/Displayable.h
        Programs/programs_source/gravity_simulation/objects/GravityObject.cpp
        Programs/programs_source/gravity_simulation/objects/GravityObject.h
        Programs/programs_source/gravity_simulation/vector_editor/VectorFigure.cpp
        Programs/programs_source/gravity_simulation/vector_editor/VectorFigure.h
        Programs/programs_source/gravity_simulation/Simulation.cpp
        Programs/programs_source/gravity_simulation/Simulation.h
        Programs/programs_source/gravity_simulation/SimulationProgram.cpp
        Programs/programs_source/gravity_simulation/SimulationProgram.h
        Programs/programs_source/gravity_simulation/TestMoveObject.h
        Programs/programs_source/gravity_simulation/UniverseConstants.h
        Programs/programs_source/gravity_simulation/gravity_main.cpp)

target_link_libraries(GravitySimulation GraphicalFramework)

add_executable(lab3
        Programs/programs_source/lab3_lighting/LightingLab3.cpp
        Programs/programs_source/lab3_lighting/LightingLab3.h
        Programs/programs_source/lab3_lighting/lab3_main.cpp)

target_link_libraries(lab3 GraphicalFramework)
