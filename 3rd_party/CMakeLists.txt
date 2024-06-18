cmake_minimum_required(VERSION 3.25)
include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)

# OFP
FetchContent_Declare(
        OFPLib
        GIT_REPOSITORY https://git.swurl.xyz/swirl/OFPLib.git
        GIT_TAG        8d3e1ead7da1c37c636280d7b64e239c6ce99e1d
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(OFPLib)
