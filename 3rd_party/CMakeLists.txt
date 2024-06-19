cmake_minimum_required(VERSION 3.25)
include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)

# OFP
FetchContent_Declare(
        OFPLib
        GIT_REPOSITORY https://git.swurl.xyz/swirl/OFPLib.git
        GIT_TAG        6241c0bb1825738c2f98fb3e419abead6bb37967
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(OFPLib)
