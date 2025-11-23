if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed, use: cmake -S . -B build")
endif()

# all runtime execs in build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)


cmake_minimum_required(VERSION 3.10)
project(MICE)

find_package(HDF5 REQUIRED)

add_executable(MICE src/main.c)


target_include_directories(MICE PRIVATE ${HDF5_INCLUDE_DIRS})
target_link_libraries(MICE PRIVATE ${HDF5_LIBRARIES})
