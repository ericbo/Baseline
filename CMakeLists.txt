cmake_minimum_required (VERSION 3.10)

project (baseline VERSION 0.1)

file(COPY src/Fonts DESTINATION ${CMAKE_BINARY_DIR})
file(COPY src/Textures DESTINATION ${CMAKE_BINARY_DIR})

add_executable(
    ${PROJECT_NAME}

    src/main.cpp
    src/Domain/Player.cpp
    src/Domain/Delta.cpp
    src/Domain/Sprite.cpp
    src/Domain/Text.cpp
    src/Domain/MultiTextBox.cpp
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