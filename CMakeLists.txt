cmake_minimum_required(VERSION 3.29)
project(mars-hopper)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(mars-hopper main.cpp
        src/entities/Hopper.cpp
        src/entities/Platform.cpp
        src/game/Game.cpp
        src/utils/RandomGenerator.cpp
        src/utils/TextureLoader.cpp
)

target_link_libraries(mars-hopper
        sfml-graphics sfml-audio)