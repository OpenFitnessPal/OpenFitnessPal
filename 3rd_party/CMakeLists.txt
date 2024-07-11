cmake_minimum_required(VERSION 3.25)
include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)

# OFP
FetchContent_Declare(
        OFPLib
        GIT_REPOSITORY https://git.swurl.xyz/swirl/OFPLib.git
        GIT_TAG        97e343798b0cf928ec468032e5a834c7ec240f0a
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(OFPLib)
