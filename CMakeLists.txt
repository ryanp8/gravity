cmake_minimum_required(VERSION 3.21)
set(PROJECT_NAME Gravity)
project(${PROJECT_NAME} LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

add_compile_options(-Wall -Ofast)
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/body.cpp
    src/node.cpp
    src/simulation.cpp
)
target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
