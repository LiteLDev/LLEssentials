cmake_minimum_required(VERSION 3.21)
project(LiteLoaderPlugins)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

include_directories(AntiToolbox)
include_directories(LLHelper)
include_directories(LLMoney)
include_directories(LLTpa)
include_directories(SDK/Header)
include_directories(Header)

file(GLOB SRC_FILES
        ${PROJECT_SOURCE_DIR}/LLTpa/*.cpp
        ${PROJECT_SOURCE_DIR}/LLTpa/*.h
        ${PROJECT_SOURCE_DIR}/LLHelper/*.cpp
        ${PROJECT_SOURCE_DIR}/LLHelper/*.h
        ${PROJECT_SOURCE_DIR}/LLMoney/*.cpp
        ${PROJECT_SOURCE_DIR}/LLMoney/*.h
        ${PROJECT_SOURCE_DIR}/AntiToolbox/*.cpp
        ${PROJECT_SOURCE_DIR}/AntiToolbox/*.h
        )

add_library(LiteLoaderPlugins SHARED ${SRC_FILES})