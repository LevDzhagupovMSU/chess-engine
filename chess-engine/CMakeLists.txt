cmake_minimum_required(VERSION 3.20)
project(ChessEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Предупреждения компилятора
add_library(project_warnings INTERFACE)

# Разные предупреждения в зависимости от компилятора
if(MSVC)
    target_compile_options(project_warnings INTERFACE /W4 /WX)
else()
    target_compile_options(project_warnings INTERFACE 
        -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor -Wunused
    )
endif()

# Основной исполняемый файл
add_executable(chess_engine
    src/main.cpp

    # core
    src/core/piece.cpp
    src/core/pawn.cpp
    src/core/knight.cpp
    src/core/bishop.cpp
    src/core/rook.cpp
    src/core/queen.cpp
    src/core/king.cpp
    src/core/history.cpp
    src/core/board.cpp
    src/core/board_checks.cpp

    # ai
    src/ai/evaluation.cpp
    src/ai/search.cpp
)

target_include_directories(chess_engine PRIVATE include)
target_link_libraries(chess_engine PRIVATE project_warnings)

# Оптимизация для Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
endif()