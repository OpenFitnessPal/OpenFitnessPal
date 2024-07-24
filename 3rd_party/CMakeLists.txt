cmake_minimum_required(VERSION 3.25)
include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)

# OFP
FetchContent_Declare(
        OFPLib
        GIT_REPOSITORY https://github.com/crueter/OFPLib.git
        GIT_TAG        5387f2f04c8d7e5903db14df05ab1b6736ce1d96
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(OFPLib)
