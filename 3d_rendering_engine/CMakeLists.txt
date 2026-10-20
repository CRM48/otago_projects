
cmake_minimum_required(VERSION 3.12)
project(COSC_RenderEngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

include(FetchContent)

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.10
)

# GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)

# Assimp
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG v5.4.3
)

FetchContent_MakeAvailable(glfw glm assimp)

# Application
add_executable(Skeleton
    Skeleton/renderApp.cpp

    common/Shader.cpp
    common/Quad.cpp
    common/Texture.cpp
    common/Camera.cpp
    common/Scene.cpp
    common/Object.cpp
    common/MTLShader.cpp
    common/Mesh.cpp
    common/Material.cpp
    common/Group.cpp
    common/Objloader.cpp
    common/Controls.cpp
    common/Triangle.cpp
    common/BasicMaterialShader.cpp

    Skeleton/basicShader.vert
    Skeleton/basicShader.frag
    Skeleton/phongShader.vert
    Skeleton/phongShader.frag
    Skeleton/blinnPhongShader.vert
    Skeleton/blinnPhongShader.frag
    Skeleton/postEffect.vert
    Skeleton/postEffect.frag
)

target_include_directories(Skeleton PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

target_compile_definitions(Skeleton PRIVATE
    USE_ASSIMP
    GLM_ENABLE_EXPERIMENTAL
)

target_link_libraries(Skeleton PRIVATE
    OpenGL::GL
    glfw
    glm::glm
    assimp
)
