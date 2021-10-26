project(UnitTest)

file(
    GLOB SRC

    Domain/*.cpp
)

add_executable(
        ${PROJECT_NAME}

        ${SRC}
)

target_link_libraries(
        ${PROJECT_NAME}

        libbaseline
        ${GTEST_BOTH_LIBRARIES}
        pthread
)