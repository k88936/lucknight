cmake_minimum_required(VERSION 3.28)
project(lucknight)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_definitions(-DENTT_ID_TYPE=std::uintptr_t)

add_subdirectory(box2d)
add_subdirectory(QRenderer2D)

# for entt entity type the same size with box2d userData( void* )
add_subdirectory(entt)
add_subdirectory(enkiTS)
add_subdirectory(preprocessor)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
set(LUCKNIGHT_FILES
        src/Systems/System.cpp
        src/Utils/Singletion.cpp
        src/Managers/EventManager.cpp
        src/Managers/TextureManager.cpp
        src/Systems/KeyboardControlSystem.cpp
        src/Systems/AnimationSystem.cpp
        src/Core/World.cpp
        src/Prefab/Prefab.cpp
        src/Prefab/PrefabPlayer.cpp
        src/Systems/PhysicsSystem.cpp
        src/Systems/ScriptSystem.cpp
        src/Scripts/PlayerScript.cpp
        src/Prefab/PrefabPlatform.cpp
        src/Prefab/PrefabProjectile.cpp
        src/Scripts/ProjectileScript.cpp
        src/Systems/HealthSystem.cpp
        src/Prefab/PrefabWeapon.cpp
        src/Prefab/PrefabWeapon.h
        src/Events/BodyEvents.h
        src/Events/WeaponShootEvent.h
        src/Systems/WeaponSystem.cpp
        src/Systems/WeaponSystem.h
        src/Prefab/PrefabTreasure.cpp
        src/Prefab/PrefabTreasure.h
        src/Events/GainEvents.h
        src/Systems/AttachmentSystem.cpp
        src/Systems/AttachmentSystem.h
        src/Systems/TreasureSystem.cpp
)
add_executable(lucknight
        src/main.cpp
        src/Core/Scene.cpp
        ${LUCKNIGHT_FILES}
        src/Prefab/PrefabIndicator.cpp
        src/Prefab/PrefabIndicator.h
        src/Scripts/IndicatorScript.cpp
        src/Scripts/IndicatorScript.h
)
add_executable(lucknight_box2d_sample
        samples/main.cpp
        ${LUCKNIGHT_FILES}
)
target_link_libraries(lucknight
        Qt::Core
        Qt::Gui
        Qt::Widgets
        boost_preprocessor
        QRenderer2D
        box2d::box2d
        EnTT::EnTT
        enkiTS
)

target_link_libraries(lucknight_box2d_sample
        Qt::Core
        Qt::Gui
        boost_preprocessor
        QRenderer2D
        box2d::box2d
        EnTT::EnTT
        enkiTS
        samples
)
