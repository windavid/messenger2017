cmake_minimum_required(VERSION 3.4)

project(test-app)

add_compile_options(-std=c++11 -ggdb -O0)

# -------------------------   sources   -------------------------
set(SOURCES
    test.cpp
    )

include_directories(${SUBPROJECT_ROOT})
include_directories(${SUBPROJECT_ROOT}/include)
include_directories(${SUBPROJECT_ROOT}/../shared_client)
include_directories(${SHARED_ROOT}/include)

# --------------------------------------------------------------

if (WIN32)
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    SET(BUILD_SHARED_LIBRARIES OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
endif()

# ------------------------  PATH ----------------------------
get_filename_component(M2_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
get_filename_component(M2_GLOBAL_3RD_PARTY "${M2_ROOT}/../../../3rd-party" ABSOLUTE)
get_filename_component(M2_3RD_PARTY "${M2_ROOT}/3rd-party" ABSOLUTE)

set (CMAKE_MODULE_PATH "${M2_GLOBAL_3RD_PARTY};${M2_GLOBAL_3RD_PARTY}/cmake;")

# -------------------------    DEPENDENCIES   --------------------------

find_package(Boost COMPONENTS REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

find_package(Libevent REQUIRED)
include_directories(${LIBEVENT_INCLUDE_DIRS})

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

find_package(Threads)

# -------------------------    boost   --------------------------
find_package(Boost COMPONENTS REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable (${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} m2-core)

