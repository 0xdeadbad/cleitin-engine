cmake_minimum_required(VERSION 3.10)

project(cleitin_engine LANGUAGES C VERSION 0.0.1)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(CMAKE_DIR ${CMAKE_SOURCE_DIR}/cmake)

set(cleitin_LIB_DIR ${SRC_DIR}/cleitin)

set(module_DIR ${cleitin_LIB_DIR}/module)
set(module_INCLUDE_DIR ${INCLUDE_DIR}/module)
set(module_FILES 
    ${module_DIR}/ecs.c
    ${module_DIR}/draw.c
)
add_library(module STATIC ${module_FILES})
target_include_directories(module
    PRIVATE
    ${module_INCLUDE_DIR}
)
target_link_libraries(module
    PRIVATE
    luajit-5.1
    pthread
    flecs
    raylib
    dl
)

set(cleitin_INCLUDE_DIR ${INCLUDE_DIR}/cleitin)
set(cleitin_LIB_FILES
    ${cleitin_LIB_DIR}/cleitin.c
)
add_library(cleitin_lib SHARED ${cleitin_LIB_FILES})
target_include_directories(cleitin_lib
    PRIVATE
    ${cleitin_INCLUDE_DIR}
    ${module_INCLUDE_DIR}
)
target_link_libraries(cleitin_lib
    PRIVATE
    module
)

set(main_FILES
    ${SRC_DIR}/main.c
)
add_executable(${PROJECT_NAME} ${main_FILES})
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${module_INCLUDE_DIR}
    ${cleitin_INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    cleitin_lib
)