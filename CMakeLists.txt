cmake_minimum_required(VERSION 3.16)
project(HYDRO-STATIC CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(Core)

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE Core)

# Setting ASSETS_PATH
# target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH=
#                            "${CMAKE_CURRENT_SOURCE_DIR}/assets/")
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets")
