set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(yaml-cpp REQUIRED)

add_compile_options(-std=c++11)
add_executable(${PROJECT_NAME} main.cpp widget.cpp)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets yaml-cpp)
