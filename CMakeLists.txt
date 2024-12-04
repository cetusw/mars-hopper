cmake_minimum_required(VERSION 3.29)
project(mars-hopper)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(mars-hopper main.cpp
        src/entities/Platform.cpp
        src/entities/Platform.h
        src/game/Game.cpp
        src/game/Game.h
        src/utils/randomGenerator.cpp
        src/entities/Vehicle.h
        src/entities/Vehicle.cpp
        src/entities/Landscape.h
        src/entities/Landscape.cpp
        src/entities/Screen.h
        src/entities/Screen.cpp
        src/utils/loadTexture.cpp
        src/utils/loadFont.cpp
        src/utils/GameState.h
        src/entities/Engine.h
        src/entities/Engine.cpp
        src/utils/constants.h
        src/utils/loadSound.cpp
)

target_link_libraries(mars-hopper
        sfml-graphics sfml-audio)