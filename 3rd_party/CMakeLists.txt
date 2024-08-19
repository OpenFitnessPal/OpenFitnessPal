cmake_minimum_required(VERSION 3.25)
include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)

# OFP
FetchContent_Declare(
        OFPLib
        GIT_REPOSITORY https://git.swurl.xyz/OpenFitnessPal/lib.git/
        GIT_TAG        dcff82d1490b8662b6137d0a979df35079234db4
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(OFPLib)
