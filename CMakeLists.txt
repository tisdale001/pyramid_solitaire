# Your CMakeLists.txt for the main test project
cmake_minimum_required(VERSION 3.10)

project(
    prog
    VERSION 1.0
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)


include_directories("./include/")

# link_directories("/usr/lib/x86_64-linux-gnu/")

add_executable(prog ./ControllerPyramid.cpp ./ViewPyramid.cpp ./ModelPyramid.cpp ./Node.cpp ./Card.cpp 
./Deck.cpp ./AnimationWrapper.cpp)

target_compile_options(prog PRIVATE -Wall -Wextra -Wpedantic)

target_link_libraries(prog sfml-graphics sfml-window sfml-system)