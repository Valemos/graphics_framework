cmake_minimum_required(VERSION 3.17)
project(GraphicalFramework)

set(CMAKE_CXX_STANDARD 14)

include_directories(D:/coding/cpp_libs/GLM)
include_directories(D:/coding/cpp_libs/GLEW/include)
include_directories(D:/coding/cpp_libs/GLFW/include)
include_directories(Framework)
include_directories(Framework/2d_objects)
include_directories(Framework/basic_3d_objects)
include_directories(Framework/draw_objects)
include_directories(Programs/programs_source)
include_directories(Programs/programs_source/gravity_simulation)
include_directories(Programs/programs_source/gravity_simulation/objects)
include_directories(Programs/programs_source/gravity_simulation/vector_editor)
include_directories(Vector/source)
include_directories(D:/coding/cpp_libs/stb_image)

add_library(GraphicalFramework
        Framework/2d_objects/Grid2D.cpp
        Framework/2d_objects/Grid2D.h
        Framework/basic_3d_objects/AxisObject.h
        Framework/basic_3d_objects/Cube.h
        Framework/basic_3d_objects/Dodecahedron.h
        Framework/basic_3d_objects/Sphere.h
        Framework/basic_3d_objects/Surface.h
        Framework/draw_objects/Camera.cpp
        Framework/draw_objects/Camera.h
        Framework/draw_objects/Drawable.h
        Framework/draw_objects/Figure2D.cpp
        Framework/draw_objects/Figure2D.h
        Framework/draw_objects/primitives/Line.cpp
        Framework/draw_objects/primitives/Line.h
        Framework/draw_objects/Object3D.cpp
        Framework/draw_objects/Object3D.h
        Framework/draw_objects/primitives/Primitive.cpp
        Framework/draw_objects/primitives/Primitive.h
        Framework/draw_objects/primitives/Quad.cpp
        Framework/draw_objects/primitives/Quad.h
        Framework/draw_objects/primitives/Triangle.cpp
        Framework/draw_objects/primitives/Triangle.h
        Framework/draw_objects/primitives/TriangleFan.cpp
        Framework/draw_objects/primitives/TriangleFan.h
        Framework/ButtonHandler.cpp
        Framework/ButtonHandler.h
        Framework/Program.h
        Framework/ProgramInputHandler.cpp
        Framework/ProgramInputHandler.h
        Framework/Renderer.cpp
        Framework/Renderer.h
        Vector/source/Vector3.cpp
        Vector/source/Vector3.h
        Framework/draw_objects/NormalMapped.cpp
        Framework/draw_objects/NormalMapped.h
        Framework/draw_objects/VertexPrimitives.cpp
        Framework/draw_objects/VertexPrimitives.h
        Test/test_main.cpp
        Framework/SphericalCamera.cpp
        Framework/SphericalCamera.h Framework/draw_objects/LightSource.h Framework/draw_objects/TexturedObject3d.cpp Framework/draw_objects/TexturedObject3d.h Framework/draw_objects/Texture.cpp Framework/draw_objects/Texture.h Framework/basic_3d_objects/TexturedSphere.cpp Framework/basic_3d_objects/TexturedSphere.h)


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
        Test/Test2DObject.h
        Test/Test3DObject.h
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

add_executable(test
        Test/TestNormals.h
        Test/Test2DObject.h
        Test/Test3DObject.h
        Test/test_main.cpp)

target_link_libraries(test GraphicalFramework)