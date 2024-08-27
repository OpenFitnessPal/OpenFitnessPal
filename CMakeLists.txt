
cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

set(CMAKE_CXX_STANDARD 17)

set(OFP_ORG_NAME "OpenFitnessPal")
set(OFP_APP_NAME "OFPApp")
set(OFP_EXEC_NAME "OpenFitnessPal")
set(OFP_GIT_REPO "https://github.com/crueter/QMLTest.git")

project(${OFP_APP_NAME} VERSION 0.1 LANGUAGES CXX)

add_subdirectory(3rd_party)
find_package(OFPLib)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
    CACHE STRING "Import paths for Qt Creator's code model"
    FORCE
)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Qml Quick)

set(CODE_ELEMENTS
    data/DataManager
    data/CacheManager
    data/SettingsManager

    Recipe
    ExerciseRoutine

    GoalManager
    NutritionManager
    PlatformHelper

    models/FoodServingModel
    models/FoodServingComboBoxModel
    models/RecipeListModel

    models/ExerciseListModel
    models/ExerciseSetsModel
    models/ExerciseRoutinesModel

    models/NutrientModel

    items/Exercise
    items/ExerciseSet
)

foreach(ELEMENT ${CODE_ELEMENTS})
    set(HEADERS ${HEADERS} include/${ELEMENT}.h)
    set(SOURCES ${SOURCES} src/${ELEMENT}.cpp)
endforeach()

if(WIN32)
    set(RCS_FILE ${CMAKE_CURRENT_BINARY_DIR}/program_info/${OFP_EXEC_NAME}.rc)
    set(OFP_BUILD_PLATFORM "win32")
elseif(ANDROID)
    set(MANIFEST_FILE android/AndroidManifest.xml)
    set(OFP_BUILD_PLATFORM "android")
else()
    set(OFP_BUILD_PLATFORM "lin64")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/)

# Git
include(GetGitRevisionDescription)
git_get_exact_tag(OFP_GIT_TAG)
get_git_head_revision(OFP_GIT_REFSPEC OFP_GIT_COMMIT)

message(STATUS "Git commit: ${OFP_GIT_COMMIT}")
message(STATUS "Git tag: ${OFP_GIT_TAG}")
message(STATUS "Git refspec: ${OFP_GIT_REFSPEC}")

string(REPLACE "-beta" "." OFP_GIT_TAG_NUMERO ${OFP_GIT_TAG})

string(REPLACE "." " " OFP_SPLIT_VERSION ${OFP_GIT_TAG_NUMERO})

separate_arguments(OFP_SPLIT_VERSION)

list(GET OFP_SPLIT_VERSION 0 OFP_VERSION_MAJOR)
list(GET OFP_SPLIT_VERSION 1 OFP_VERSION_MINOR)
list(GET OFP_SPLIT_VERSION 2 OFP_VERSION_HOTFIX)

project(${OFP_APP_NAME} VERSION ${OFP_GIT_TAG_NUMERO} LANGUAGES CXX)

# Build Date
string(TIMESTAMP TODAY "%Y-%m-%d")
set(OFP_BUILD_TIMESTAMP "${TODAY}")

add_subdirectory(buildconfig)

set(PROJECT_SRC ${HEADERS} ${SOURCES}
    ${RCS_FILE}
    ${MANIFEST_FILE}

    ${OFPLib_SOURCE_DIR}/include/OFPManager.h
    ${OFPLib_SOURCE_DIR}/include/FoodItem.h
    ${OFPLib_SOURCE_DIR}/include/ServingSize.h
    ${OFPLib_SOURCE_DIR}/include/NutrientUnion.h

    ${CMAKE_BINARY_DIR}/buildconfig/BuildConfig.cpp
)

qt_add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SRC})
qt_add_resources(${CMAKE_PROJECT_NAME} "configuration"
    PREFIX "/"
    FILES
    qtquickcontrols2.conf)

qt_add_qml_module(${OFP_APP_NAME}
    URI OFPNative
    VERSION 1.0
    SOURCES
    ${PROJECT_SRC}
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME ${OFP_EXEC_NAME})

add_subdirectory(program_info/)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
)

if(UNIX AND APPLE)
    # Mac bundle settings
    set(MACOSX_BUNDLE_BUNDLE_NAME "${OFP_EXEC_NAME}")
    set(MACOSX_BUNDLE_INFO_STRING "${OFP_EXEC_NAME}: A free, open-source fitness tracker.")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.${OFP_ORG_NAME}.${OFP_EXEC_NAME}")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "${OFP_GIT_TAG_NUMERO}")
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${OFP_GIT_TAG_NUMERO}")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING "${OFP_GIT_TAG_NUMERO}")
    set(MACOSX_BUNDLE_ICON_FILE ${OFP_EXEC_NAME}.icns)
    set(MACOSX_BUNDLE_COPYRIGHT "Copyleft 2024 ${OFP_ORG_NAME}")

    # install as bundle
    set(INSTALL_BUNDLE "full")
endif()

if (ANDROID)
    include(FetchContent)
    FetchContent_Declare(
        android_openssl
        DOWNLOAD_EXTRACT_TIMESTAMP true
        URL https://github.com/KDAB/android_openssl/archive/refs/heads/master.zip
    )
    FetchContent_MakeAvailable(android_openssl)
    include(${android_openssl_SOURCE_DIR}/android_openssl.cmake)
endif()

if (ANDROID)
    add_android_openssl_libraries(${OFP_APP_NAME})
endif()

target_include_directories(${OFP_APP_NAME} PRIVATE "include/")
target_include_directories(${OFP_APP_NAME} PRIVATE "include/items")
target_include_directories(${OFP_APP_NAME} PRIVATE "include/data")
target_include_directories(${OFP_APP_NAME} PRIVATE "include/models")
target_include_directories(${OFP_APP_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${OFPLib_SOURCE_DIR}/include)

include(qds)

if (BUILD_QDS_COMPONENTS)
    include(qmlcomponents OPTIONAL)
endif()

if (LINK_INSIGHT)
    include(insight OPTIONAL)
endif ()

include(GNUInstallDirs)
install(TARGETS ${CMAKE_PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
