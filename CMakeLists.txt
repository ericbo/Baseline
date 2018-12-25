project (baseline)

cmake_minimum_required (VERSION 3.10)

add_executable(
  baseline

  src/main.cpp
)

find_package(Vulkan REQUIRED)
target_link_libraries(baseline Vulkan::Vulkan)