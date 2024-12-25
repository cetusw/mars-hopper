cmake_minimum_required(VERSION 3.29)
project(mars-hopper)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(mars-hopper main.cpp
        src/entities/Platform.cpp
        src/entities/Platform.h
        src/game/Game.cpp
        src/game/Game.h
        src/entities/Vehicle.h
        src/entities/Vehicle.cpp
        src/entities/Landscape.h
        src/entities/Landscape.cpp
        src/entities/Screen.h
        src/entities/Screen.cpp
        src/utils/GameState.h
        src/entities/Flame.h
        src/entities/Flame.cpp
        src/utils/constants.h
        src/entities/Meteorite.h
        src/entities/Meteorite.cpp
        src/utils/utils.cpp
        src/entities/Speedometer.h
        src/entities/Speedometer.cpp
        src/entities/FuelIndicator.h
        src/entities/FuelIndicator.cpp
        src/entities/PassedPlatforms.h
        src/entities/PassedPlatforms.cpp
        src/entities/AchievementManager.h
        src/entities/AchievementManager.cpp
        src/entities/MiniMap.h
        src/entities/MiniMap.cpp
        src/entities/SafetyFactor.h
        src/entities/SafetyFactor.cpp
        src/entities/RepairKitIndicator.h
        src/entities/RepairKitIndicator.cpp
        src/utils/GameDifficulty.h
)

target_link_libraries(mars-hopper
        sfml-graphics sfml-audio)