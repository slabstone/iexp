cmake_minimum_required(VERSION 3.16)
project(iexp C)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_subdirectory(src)

# build log.c submodule
set(LOG_C_TARGET_NAME log.c)
set(LOG_C_SOURCE_DIR ${CMAKE_SOURCE_DIR}/log.c/src)

add_library(${LOG_C_TARGET_NAME} STATIC
  ${LOG_C_SOURCE_DIR}/log.h
  ${LOG_C_SOURCE_DIR}/log.c
)

set_target_properties(${LOG_C_TARGET_NAME} PROPERTIES C_STANDARD 99)
target_compile_definitions(${LOG_C_TARGET_NAME} PRIVATE LOG_USE_COLOR)
target_include_directories(${LOG_C_TARGET_NAME} SYSTEM INTERFACE ${LOG_C_SOURCE_DIR})
