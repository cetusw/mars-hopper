cmake_minimum_required(VERSION 3.29)
project(mars-hopper)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(mars-hopper main.cpp
        src/entities/Platform.cpp
        src/game/Game.cpp
        src/utils/RandomGenerator.cpp
        src/utils/TextureLoader.cpp
        src/entities/GameBackground.h
        src/entities/GameBackground.cpp
        src/entities/Vehicle.h
        src/entities/Vehicle.cpp
        src/entities/Landscape.h
        src/entities/Landscape.cpp
)

target_link_libraries(mars-hopper
        sfml-graphics sfml-audio)