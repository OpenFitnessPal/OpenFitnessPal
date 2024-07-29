cmake_minimum_required(VERSION 3.25)
include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)

# OFP
FetchContent_Declare(
        OFPLib
        GIT_REPOSITORY https://github.com/crueter/OFPLib.git
        GIT_TAG        937297fe9a618c8c53edac6f565817c7072122a3
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(OFPLib)
