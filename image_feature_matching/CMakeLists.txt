cmake_minimum_required(VERSION 3.12)

project(ImageFeatureMatching LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(features
    features.cpp
    Timer.cpp
)

target_include_directories(features PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(features PRIVATE ${OpenCV_LIBS})
