cmake_minimum_required(VERSION 3.20)

project(Connect4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR
	"${CMAKE_SOURCE_DIR}/lib/SFML-3.1.0/lib/cmake/SFML"
)

find_package(SFML 3 REQUIRED COMPONENTS Graphics System Window Audio)

add_executable(Connect4
	src/main.cpp
	src/Game.cpp
	src/Button.cpp
	src/Board.cpp
	src/Menu.cpp
	src/Logic.cpp
)

target_include_directories(Connect4
	PRIVATE
	"${CMAKE_SOURCE_DIR}/include"
)

target_compile_definitions(Connect4
	PRIVATE
	ROOT="${CMAKE_SOURCE_DIR}/"
)

target_link_libraries(Connect4
	PRIVATE
	SFML::Graphics
	SFML::System
	SFML::Audio
	SFML::Window
)

add_custom_command(TARGET Connect4 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_SOURCE_DIR}/lib/SFML-3.1.0/bin"
	"$<TARGET_FILE_DIR:Connect4>"
)