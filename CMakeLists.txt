project (baseline)

cmake_minimum_required (VERSION 3.10)

add_executable(
    ${PROJECT_NAME}

    src/main.cpp
    src/Domain/Player.cpp
    src/Domain/Delta.cpp
    src/Domain/Sprite.cpp
        src/Domain/Text.cpp src/Domain/Text.h src/Domain/MultiTextBox.cpp src/Domain/MultiTextBox.h)

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