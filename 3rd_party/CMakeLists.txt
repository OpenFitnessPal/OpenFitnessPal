cmake_minimum_required(VERSION 3.25)
include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)

# OFP
FetchContent_Declare(
        OFPLib
        GIT_REPOSITORY https://git.swurl.xyz/OpenFitnessPal/lib.git/
        GIT_TAG        4cff1c9e1f25e9c450552c839c8051a73a315d7d
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(OFPLib)
