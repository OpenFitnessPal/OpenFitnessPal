cmake_minimum_required(VERSION 3.25)
include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)

# OFP
FetchContent_Declare(
        OFPLib
        GIT_REPOSITORY https://git.swurl.xyz/swirl/OFPLib.git
        GIT_TAG        f1b5e3be4225fbf4b6be9db9fed8f1f491f6039a
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(OFPLib)
