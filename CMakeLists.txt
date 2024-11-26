cmake_minimum_required(VERSION 3.29)
project(mars-hopper)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(mars-hopper main.cpp
        src/entities/Platform.cpp
        src/entities/Platform.h
        src/game/Game.cpp
        src/game/Game.h
        src/utils/RandomGenerator.cpp
        src/entities/Vehicle.h
        src/entities/Vehicle.cpp
        src/entities/Landscape.h
        src/entities/Landscape.cpp
        src/entities/MainMenu.h
        src/entities/MainMenu.cpp
        src/utils/LoadTexture.h
        src/utils/LoadTexture.cpp
        src/utils/LoadTexture.cpp
        src/utils/LoadFont.cpp
        src/utils/LoadFont.h
        src/utils/GameState.h
        src/entities/Settings.h
        src/entities/Settings.cpp
)

target_link_libraries(mars-hopper
        sfml-graphics sfml-audio)