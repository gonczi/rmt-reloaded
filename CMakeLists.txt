cmake_minimum_required(VERSION 3.0.0)
project(rmt VERSION 0.1.0)

file(COPY img DESTINATION .)
file(COPY maze DESTINATION .)
file(COPY var DESTINATION .)

include(CTest)
enable_testing()

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
message(${CURSES_LIBRARY})
include_directories(${CURSES_INCLUDE_DIR})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(rmt ${SOURCES})
target_link_libraries(rmt ${CURSES_LIBRARIES} ${SDL2_LIBRARIES} Threads::Threads)
target_compile_options(rmt PRIVATE "-Wno-write-strings")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
