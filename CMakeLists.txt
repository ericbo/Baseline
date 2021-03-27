project (baseline)

cmake_minimum_required (VERSION 3.10)

add_executable(
    ${PROJECT_NAME}

  src/main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
)