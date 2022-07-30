cmake_minimum_required(VERSION 3.10)

project(cleitin_engine LANGUAGES C VERSION 0.0.1)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(CMAKE_DIR ${CMAKE_SOURCE_DIR}/cmake)
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)

set(cleitin_LIB_DIR ${SRC_DIR}/cleitin)

set(util_INCLUDE_DIR ${INCLUDE_DIR}/util)
set(network_INCLUDE_DIR ${INCLUDE_DIR}/network)
set(luajit_INCLUDE_DIR ${EXTERNAL_DIR}/LuaJIT/src)

set(ENET_SHARED 1)
add_subdirectory(${CMAKE_DIR}/enet)

#set(BUILD_SHARED_LIBS 1)
#set(LUAJIT_BUILD_EXE 0)
option(BUILD_SHARED_LIBS "" ON)
option(LUAJIT_BUILD_EXE "" OFF)
set(LUAJIT_DIR ${EXTERNAL_DIR}/LuaJIT)
add_subdirectory(${CMAKE_DIR}/luajit-cmake)

set(module_DIR ${cleitin_LIB_DIR}/module)
set(module_INCLUDE_DIR ${INCLUDE_DIR}/module)
set(module_FILES 
    ${module_DIR}/ecs.c
    ${module_DIR}/draw.c
    ${module_DIR}/window.c
    ${module_DIR}/network.c
)
add_library(module STATIC ${module_FILES})
target_include_directories(module
    PRIVATE
    ${module_INCLUDE_DIR}
    ${util_INCLUDE_DIR}
    ${network_INCLUDE_DIR}
    ${luajit_INCLUDE_DIR}
)
target_link_libraries(module
    PRIVATE
    libluajit
    pthread
    flecs
    raylib
    dl
    enet_shared
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
    ${util_INCLUDE_DIR}
    ${luajit_INCLUDE_DIR}
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
    ${util_INCLUDE_DIR}
    ${luajit_INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    cleitin_lib
)