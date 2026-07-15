cmake_minimum_required(VERSION 4.0)
project(PhosphorusGUI VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER "C:/ProgramData/mingw64/mingw64/bin/gcc.exe")

option(BUILD_SHARED_LIBS "Build using a shared library." ON)

include(FetchContent)
FetchContent_Declare(vibrant_logs GIT_REPOSITORY https://github.com/loganjellis/VibrantLogs.git GIT_TAG main)
FetchContent_Declare(dynamic_array_spellbook GIT_REPOSITORY https://github.com/loganjellis/DynamicArraySpellbook.git GIT_TAG main)
FetchContent_Declare(dynamic_map_spellbook GIT_REPOSITORY https://github.com/loganjellis/DynamicMapSpellbook.git GIT_TAG main)
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)
FetchContent_MakeAvailable(vibrant_logs dynamic_array_spellbook dynamic_map_spellbook raylib)

add_library(phosphorus_gui "${CMAKE_CURRENT_SOURCE_DIR}/src/phosphorus_gui.c")

target_compile_definitions(phosphorus_gui PRIVATE $<$<BOOL:${BUILD_SHARED_LIBS}>:PHOS_GUI_EXPORTS>)

target_include_directories(phosphorus_gui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(phosphorus_gui PUBLIC vibrant_logs dynamic_array_spellbook dynamic_map_spellbook raylib)
