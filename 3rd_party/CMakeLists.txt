cmake_minimum_required(VERSION 3.25)
include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)

# OFP
FetchContent_Declare(
        OFPLib
        GIT_REPOSITORY https://git.swurl.xyz/swirl/OFPLib.git
        GIT_TAG        a7b006ed495c119c569c1de5b909d6c2e2371bc7
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(OFPLib)
