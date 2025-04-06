cmake_minimum_required(VERSION 3.15)
project(Splitter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(SRC_OUTPUT_DIR ${CMAKE_BINARY_DIR}/src)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")


# SDL2 setup
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

file(GLOB PAGE_SOURCES "${SRC_DIR}/pages/*.cpp")
file(GLOB VARIABLES_SOURCES "${SRC_DIR}/styles/*.cpp")
add_executable(splitter ${SRC_DIR}/splitter.cpp ${PAGE_SOURCES} ${SRC_DIR}/assets/asset_loader.cpp ${VARIABLES_SOURCES} clayman.cpp)

set_target_properties(splitter PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SRC_OUTPUT_DIR})
target_link_libraries(splitter PRIVATE 
    SDL2::SDL2main
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf
    SDL2_image::SDL2_image
)

file(COPY ${SRC_DIR}/assets/images DESTINATION ${SRC_OUTPUT_DIR}/assets)
file(COPY ${SRC_DIR}/assets/fonts DESTINATION ${SRC_OUTPUT_DIR}/assets)

#rm -rf build/*
#cmake -S . -B build -G "MinGW Makefiles"
#cmake --build build