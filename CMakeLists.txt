cmake_minimum_required(VERSION 3.25)

set(OFP_ORG_NAME "OpenFitnessPal")
set(OFP_APP_NAME "OpenFitnessPal")
set(OFP_GIT_REPO "https://git.swurl.xyz/swirl/${OFP_APP_NAME}.git")

project(${OFP_APP_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Network)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

if (${FORCE_QT6})
    set(QT_VERSION_MAJOR 6)
elseif (${FORCE_QT5})
    set(QT_VERSION_MAJOR 5)
endif()

set(QT_VERSION_MAJOR 6)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Network)

# link_directories(/usr/local/lib)
# set(OFPLib_DIR "/usr/local/share/OFPLib/cmake")
# find_package(OFPLib REQUIRED)

set(UI_ELEMENTS
    MainWindow

    pages/JournalPage
    pages/ExercisePage
    pages/SettingsPage
    pages/GoalsPage
    pages/RecipesPage

    items/MealLog
    items/FoodInfoWidget
    items/RecipeInfoWidget
    items/ExerciseSet
    items/Exercise
    items/MacroPreview
    items/NutrientProgressBar

    dialogs/FoodServingEdit
    dialogs/RecipeEdit
    dialogs/RecipeAdd
    dialogs/FoodSearch
    dialogs/NutrientDialog
)

set(CODE_ELEMENTS
    data/DataManager
    data/CacheManager

    Settings
    Recipe
)

add_subdirectory(3rd_party)
find_package(OFPLib)

foreach(ELEMENT ${UI_ELEMENTS})
    set(HEADERS ${HEADERS} include/${ELEMENT}.h)
    set(SOURCES ${SOURCES} src/${ELEMENT}.cpp)
    set(UI ${UI} ui/${ELEMENT}.ui)
endforeach()

foreach(ELEMENT ${CODE_ELEMENTS})
    set(HEADERS ${HEADERS} include/${ELEMENT}.h)
    set(SOURCES ${SOURCES} src/${ELEMENT}.cpp)
endforeach()

if(ANDROID)
    set(ANDROID_GUI ON)
    set(MANIFEST_FILE ${CMAKE_CURRENT_SOURCE_DIR}/android/AndroidManifest.xml)
endif()

if(WIN32)
    set(RCS_FILE ${CMAKE_CURRENT_BINARY_DIR}/program_info/${OFP_APP_NAME}.rc)
    set(OFP_BUILD_PLATFORM "win32")
else()
    set(OFP_BUILD_PLATFORM "lin64")
endif()

set(PROJECT_SOURCES
    main.cpp

    ${UI}
    ${HEADERS}
    ${SOURCES}

    icons.qrc
    theme/qrc/breeze.qrc

    ${RCS_FILE}
    ${MANIFEST_FILE}

    # weird moc bug
    ${OFPLib_SOURCE_DIR}/include/OFPManager.h
)

qt_wrap_ui(SOURCES ${UI})

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

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

# TODO: buildconfig

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${OFP_APP_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ${OFP_APP_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${OFP_APP_NAME} SHARED
            ${MANIFEST_FILE}
            ${PROJECT_SOURCES}
        )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
else()
    add_executable(${OFP_APP_NAME}
        ${PROJECT_SOURCES}
    )
endif()
endif()

add_subdirectory("program_info")

target_link_libraries(${OFP_APP_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network OFPLib)
target_include_directories(${OFP_APP_NAME} PRIVATE include/)
# target_include_directories(${OFP_APP_NAME} PRIVATE /usr/local/include)
# target_include_directories(${OFP_APP_NAME} PRIVATE include/setup)
target_include_directories(${OFP_APP_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
# target_include_directories(${OFP_APP_NAME} PRIVATE "$<TARGET_PROPERTY:OFPLib,INTERFACE_INCLUDE_DIRECTORIES>")
include_directories(${OFPLib_SOURCE_DIR}/include)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${OFP_APP_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if (ANDROID)
    set_target_properties(${OFP_APP_NAME} PROPERTIES
        QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/android
        COMPILE_DEFINITIONS "${COMPILE_DEFINITIONS} MOBILE")
endif()


include(GNUInstallDirs)
install(TARGETS ${OFP_APP_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${OFP_APP_NAME})
endif()
