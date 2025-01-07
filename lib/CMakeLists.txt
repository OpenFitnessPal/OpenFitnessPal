cmake_minimum_required(VERSION 3.14)

project(OFPLib LANGUAGES CXX VERSION 0.0.1 DESCRIPTION "A library to access data from MyFitnessPal's extensive nutrition database without an account.")

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network Quick)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(HEADERS
    include/FoodItem.h
    include/ServingSize.h
    include/OFPManager.h
    include/NutrientUnion.h
    include/ExerciseRoutine.h
    include/Exercise.h
    include/ExerciseSet.h
    include/Recipe.h
)

add_library(OFPLib
    src/FoodItem.cpp
    src/ExerciseRoutine.cpp
    src/Exercise.cpp
    src/ExerciseSet.cpp
    src/Recipe.cpp
    src/ServingSize.cpp
    src/OFPManager.cpp
    src/NutrientUnion.cpp
    ${HEADERS}
)

target_link_libraries(OFPLib Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Quick)

target_include_directories(OFPLib PRIVATE "include")

set_target_properties(OFPLib PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(OFPLib PROPERTIES OUTPUT_NAME "ofp")

set_target_properties(OFPLib PROPERTIES PUBLIC_HEADER "${HEADERS}")

include(GNUInstallDirs)
install(TARGETS OFPLib
    EXPORT OFPLibConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/OFP
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

export(TARGETS OFPLib
    FILE "${PROJECT_BINARY_DIR}/OFPLibTargets.cmake")


configure_file(OFPLib.pc.in OFPLib.pc @ONLY)
# install(FILES ${CMAKE_BINARY_DIR}/OFPLib.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

export(PACKAGE OFPLib)

configure_file(OFPLibConfig.cmake.in
    "${PROJECT_BINARY_DIR}/OFPLibConfig.cmake" @ONLY)

export(TARGETS
    OFPLib
    NAMESPACE OFPLib::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/OFPLibConfig.cmake"
)

install(EXPORT OFPLibConfig DESTINATION
    "${CMAKE_INSTALL_DATADIR}/OFPLib/cmake" COMPONENT dev)
