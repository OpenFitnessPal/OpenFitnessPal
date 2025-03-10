cmake_minimum_required(VERSION 3.25)
include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)

set(FETCHCONTENT_QUIET OFF)

set(QUAZIP_QT_MAJOR_VERSION 6)

FetchContent_Declare(
        quazip
        GIT_REPOSITORY http://github.com/stachenov/quazip
        GIT_TAG        3fd3b299b875fbd2beac4894b8a870d80022cad7 # 1.5
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(quazip)
