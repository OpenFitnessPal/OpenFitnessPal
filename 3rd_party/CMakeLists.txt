cmake_minimum_required(VERSION 3.25)
include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)

# OFP
FetchContent_Declare(
        OFPLib
        GIT_REPOSITORY https://git.swurl.xyz/swirl/OFPLib.git
        GIT_TAG        de7451c16f6e8f219944a40dadaf22567c634af4
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(OFPLib)
