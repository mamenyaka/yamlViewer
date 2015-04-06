cmake_minimum_required(VERSION 2.6)

project(yamlViewer)

file(COPY "src/shapes.yaml" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(src)
