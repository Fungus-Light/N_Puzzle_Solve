cmake_minimum_required(VERSION 3.0.0)
project(NPuzzleSolve VERSION 0.1.0)

set(CPPFiles 

    SRC/Status.cpp
    SRC/Util.cpp
    SRC/DFS.cpp
    SRC/BFS.cpp
    SRC/AStar.cpp
    main.cpp
)

add_executable(NPuzzleSolve ${CPPFiles})

target_include_directories(NPuzzleSolve 
    PRIVATE 
    ${PROJECT_SOURCE_DIR}/INCLUDES
)