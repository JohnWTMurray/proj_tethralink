cmake_minimum_required(VERSION 3.20.5)

set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${} -std=c++20")

find_package(PkgConfig )

project(project)

file(GLOB SOURCES src/*.cpp src/*.c)


add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
	include/
)

# somehow this fucking works fine, fuck.
target_link_libraries(${PROJECT_NAME} pthread)