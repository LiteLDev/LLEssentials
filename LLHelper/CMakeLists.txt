cmake_minimum_required(VERSION 3.21)
project(LLHelper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/x64/)
set(TARGET_DIR ${CMAKE_SOURCE_DIR}/x64/Release/)

file(GLOB SRC_FILES
        ${PROJECT_SOURCE_DIR}/*.cpp
        ${PROJECT_SOURCE_DIR}/*.h
        )

add_definitions(-D"NDEBUG" -D"_CRT_SECURE_NO_WARNINGS" -D"_WINDOWS"
        -D"_USRDLL" -D"_AMD64_" -D"NOMINMAX" -D"_WINDLL" -D"_UNICODE" -D"UNICODE")

add_compile_options(
        /permissive- /GS /GL /W3 /Gy /Zc:wchar_t /Zi /Gm- /O2 /sdl /Zc:inline /fp:precise
        /errorReport:prompt /WX- /Zc:forScope /Gd /Oi /MD /std:c++17 /FC /EHsc /nologo /diagnostics:column 
)

add_link_options(
        /MANIFEST /LTCG:incremental /NXCOMPAT /DEBUG /DLL /MACHINE:X64 /OPT:REF /INCREMENTAL:NO /SUBSYSTEM:CONSOLE
        /MANIFESTUAC:NO /OPT:ICF /ERRORREPORT:PROMPT /NOLOGO /DELAYLOAD:bedrock_server.dll /TLBID:1
)

link_directories(${CMAKE_SOURCE_DIR}/SDK/Lib/)
add_library(LLHelper SHARED ${SRC_FILES})
target_link_libraries(LLHelper LiteLoader.lib
        bedrock_server_api.lib
        bedrock_server_var.lib
        SymDBHelper.lib)

include_directories(${CMAKE_SOURCE_DIR}/SDK/Header)
include_directories(${CMAKE_SOURCE_DIR}/SDK/Header/third-party)
include_directories(${CMAKE_SOURCE_DIR}/Header)