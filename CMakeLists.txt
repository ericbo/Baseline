cmake_minimum_required (VERSION 3.10)

project (baseline VERSION 0.1)

file(COPY src/Fonts DESTINATION ${CMAKE_BINARY_DIR})
file(COPY src/Textures DESTINATION ${CMAKE_BINARY_DIR})

find_package(GTest)
set(GTEST_FOUND ${GTEST_FOUND} CACHE INTERNAL "")

if(GTEST_FOUND)
    enable_testing()
    add_subdirectory(test)
endif()

add_executable(
    ${PROJECT_NAME}

    src/main.cpp
    src/Domain/Player.cpp
    src/Domain/Delta.cpp
    src/Domain/Sprite.cpp
    src/Domain/Text.cpp
    src/Domain/MultiTextBox.cpp
    src/Services/Engine/Collisions.cpp
    src/Domain/Projectile.cpp
    src/Domain/Coordinates.cpp
)

target_link_libraries(
    ${PROJECT_NAME}

    sfml-graphics
    sfml-window
    sfml-system
    pthread
    X11
)

target_include_directories(
        ${PROJECT_NAME}

        PRIVATE src/
)

add_library(
        lib${PROJECT_NAME}

        src/Domain/Coordinates.cpp
)

target_link_libraries(
        lib${PROJECT_NAME}

        pthread
)

target_include_directories(
        lib${PROJECT_NAME}

        PUBLIC src/
)