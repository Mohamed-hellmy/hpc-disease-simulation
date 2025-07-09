cmake_minimum_required(VERSION 3.16)
project(GameOfLifeMPI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use FetchContent to download SFML if not installed locally
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

# Find other dependencies
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(MPI REQUIRED)

# Add executable
add_executable(game_of_life
    src/main.cpp
    src/GameOfLife.cpp
    src/GameOfLifeUI.cpp
    src/LocalGameOfLife.cpp
)

# Include directories
target_include_directories(game_of_life PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Link libraries
target_link_libraries(game_of_life PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    Eigen3::Eigen
    MPI::MPI_CXX
)

# Add DEBUG flag only if option is enabled (after target is defined!)
option(ENABLE_DEBUG "Enable debug logging" OFF)
if (ENABLE_DEBUG)
    target_compile_definitions(game_of_life PRIVATE DEBUG)
endif()