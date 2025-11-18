include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_LIST_DIR}/Source/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/Source/")

add_library(Core STATIC)
target_sources(Core PRIVATE ${SOURCES})
target_link_libraries(Core raylib)
target_include_directories(Core PUBLIC Source)
