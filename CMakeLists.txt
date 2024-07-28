cmake_minimum_required(VERSION 3.21)
project(Tetritime)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES src/main.cpp
        src/Game.cpp
        src/Game.h
        src/TetrisBoard.cpp
        src/TetrisBoard.h
        src/System.cpp
        src/System.h
        src/Piece.cpp
        src/Piece.h
        src/State.cpp
        src/State.h
        src/StateMachine.cpp
        src/StateMachine.h
        src/Menu.cpp
        src/Menu.h
        src/Button.cpp
        src/Button.h
        src/GameOver.cpp
        src/GameOver.h
        src/FLineGame.cpp
        src/FLineGame.h
        src/BlitzGame.cpp
        src/BlitzGame.h
)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(OPUSFILE REQUIRED IMPORTED_TARGET opusfile)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE pkg-config opusfile)
target_link_libraries(${PROJECT_NAME} PkgConfig::OPUSFILE)

target_link_libraries(${PROJECT_NAME} /home/caleb/Documents/CLionProjects/Dualie/lib/libdualie.a citro2d citro3d ctru m)
target_include_directories(${PROJECT_NAME} PUBLIC /home/caleb/Documents/CLionProjects/Dualie/include)

target_compile_options(${PROJECT_NAME} PRIVATE
        -g -O2 -Wall
)



ctr_generate_smdh(${PROJECT_NAME}.smdh
        NAME "${PROJECT_NAME}"
        DESCRIPTION "v1.0.0"
        AUTHOR "Dogbonee"
)


ctr_create_3dsx(${PROJECT_NAME}
        SMDH ${PROJECT_NAME}.smdh
        ROMFS romfs
)
