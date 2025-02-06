cmake_minimum_required(VERSION 3.16)

set(Pal_APP_NAME OpenFitnessPal)
set(Pal_EXEC_NAME OpenFitnessPal)
set(Pal_ORG_NAME ${Pal_APP_NAME})
set(Pal_GIT_REPO https://github.com/${Pal_ORG_NAME}/${Pal_App_NAME})

project(${Pal_APP_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Quick QuickControls2 Network Charts)

qt_standard_project_setup(REQUIRES 6.7)

if(WIN32)
    set(RCS_FILE ${CMAKE_CURRENT_BINARY_DIR}/program_info/${Pal_APP_NAME}.rc)
endif()

if(ANDROID)
    set(ANDROID_GUI ON)
    set(MANIFEST_FILE ${CMAKE_CURRENT_SOURCE_DIR}/android/AndroidManifest.xml)
endif()

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

# Git
include(GetGitRevisionDescription)
git_get_exact_tag(Pal_GIT_TAG)
get_git_head_revision(Pal_GIT_REFSPEC Pal_GIT_COMMIT)

message(STATUS "Git commit: ${Pal_GIT_COMMIT}")
message(STATUS "Git tag: ${Pal_GIT_TAG}")
message(STATUS "Git refspec: ${Pal_GIT_REFSPEC}")

string(REPLACE "-beta" "." Pal_GIT_TAG_NUMERO ${Pal_GIT_TAG})
string(REPLACE "-rc" "." Pal_GIT_TAG_NUMERO ${Pal_GIT_TAG_NUMERO})

string(REPLACE "." " " Pal_SPLIT_VERSION ${Pal_GIT_TAG_NUMERO})

separate_arguments(Pal_SPLIT_VERSION)

list(GET Pal_SPLIT_VERSION 0 Pal_VERSION_MAJOR)
list(GET Pal_SPLIT_VERSION 1 Pal_VERSION_MINOR)
list(GET Pal_SPLIT_VERSION 2 Pal_VERSION_HOTFIX)

project(${Pal_APP_NAME} VERSION ${Pal_GIT_TAG_NUMERO} LANGUAGES CXX)

# Build Date
string(TIMESTAMP TODAY "%Y-%m-%d")
set(Pal_BUILD_TIMESTAMP "${TODAY}")

add_subdirectory("program_info")

set(QRC_FILES
    icons.qrc
)

qt_add_executable(${Pal_EXEC_NAME}
    src/main.cpp
    ${MANIFEST_FILE}
    ${QRC_FILES}
    ${RCS_FILE}
)

set_source_files_properties(qml/Constants.qml
    PROPERTIES
    QT_QML_SINGLETON_TYPE true
)

set(ELEMENTS
    data/CacheManager
    data/ExerciseManager
    data/CardioManager
    data/RecipeManager
    data/FoodManager
    data/RoutineManager
    data/GoalManager
    data/WeightManager
    data/SearchSettingsManager
    data/MealNamesManager
    data/HealthMarkerManager

    models/MealNamesModel
    models/ExerciseSetsModel
    models/ExerciseModel
    models/ExerciseRoutineModel
    models/CardioModel
    models/FoodModel
    models/ServingSizeModel
    models/NutrientModel
)

set(LIB_ELEMENTS
    FoodItem
    ServingSize
    OFPManager
    NutrientUnion
    ExerciseRoutine
    Exercise
    ExerciseSet
    Recipe
    Cardio
)

foreach(ELEMENT ${ELEMENTS})
    set(HEADERS ${HEADERS} include/${ELEMENT}.h)
    set(SOURCES ${SOURCES} src/${ELEMENT}.cpp)
endforeach()

foreach(ELEMENT ${LIB_ELEMENTS})
    set(HEADERS ${HEADERS} lib/include/${ELEMENT}.h)
    set(SOURCES ${SOURCES} lib/src/${ELEMENT}.cpp)
endforeach()

set(HEADERS
    ${HEADERS}
)

set(SOURCES
    ${SOURCES}
)

add_subdirectory(buildconfig)

### Main
set(QML_ELEMENTS
    Main
    Constants

    screen/MainScreen

    dialogs/AnimatedDialog

    # Date Picker
    dialogs/date/DatePicker
    dialogs/date/MonthSpinBox
    dialogs/date/YearSpinBox

    # items
    items/LabeledCheckbox
    items/GoalComboBox
    items/DateSelector
    items/SectionHeader
    items/BetterButton

    items/UnlabeledTextField

    items/SmallNumberField
    items/LabeledNumberField

    # Settings
    pages/settings/SettingsPage
    pages/settings/InitialPage
    pages/settings/SettingsIcon
    pages/settings/SettingsButton
    pages/settings/BaseSettingsTab

    ## Meals
    pages/settings/meals/MealsTab
    pages/settings/meals/MealNames
    pages/settings/meals/MealNameView

    ## Goals
    pages/settings/goals/GoalsTab
    pages/settings/goals/MacroGoal
    pages/settings/goals/MacrosPage
    pages/settings/goals/MicrosPage
    pages/settings/goals/MacroPresetDialog

    pages/settings/goals/GoalField
    pages/settings/goals/WeightGoalDialog

    ## Search
    pages/settings/search/SearchTab

    # Overview
    pages/overview/OverviewPage

    # Exercises
    pages/exercise/ExerciseTab
    pages/exercise/ExercisePage
    pages/exercise/ExerciseIndexPage
    pages/exercise/Exercise
    pages/exercise/ExerciseSet
    pages/exercise/ExerciseList

    ## Routines
    pages/exercise/routines/RoutinesTab
    pages/exercise/routines/RoutinePreview
    pages/exercise/routines/RoutineEdit

    ## Cardio
    pages/exercise/cardio/CardioTab
    pages/exercise/cardio/CardioPreview
    pages/exercise/cardio/CardioPresetDialog
    pages/exercise/cardio/CardioEdit

    # Food
    pages/food/FoodPage
    pages/food/MealLog
    pages/food/FoodPreview
    pages/food/FoodTab
    pages/food/FoodEdit

    pages/food/ServingSizeDialog

    ## Nutrition
    pages/food/nutrition/NutritionPreview
    pages/food/nutrition/NutritionView
    pages/food/nutrition/NutrientView

    ## Search
    pages/food/search/FoodSearch
    pages/food/search/FoodSearchPage

    # Util
    util/NavButton
    util/IconButton
    util/IconTabButton
    util/BetterStackView
)

foreach(QML ${QML_ELEMENTS})
    set(QML_FILES ${QML_FILES} qml/${QML}.qml)
endforeach()

qt_add_qml_module(${Pal_EXEC_NAME}
    URI ${Pal_EXEC_NAME}
    OUTPUT_DIRECTORY ${Pal_EXEC_NAME}_qml
    VERSION 1.0
    QML_FILES ${QML_FILES}

    SOURCES ${SOURCES} ${HEADERS}
    SOURCES include/data/NutritionManager.h src/data/NutritionManager.cpp
    QML_FILES qml/pages/food/nutrition/DaysBackDialog.qml
)

set(QML_IMPORT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS ${QML_IMPORT_PATH})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${Pal_EXEC_NAME} PROPERTIES
    #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${Pal_EXEC_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(${Pal_EXEC_NAME}
    PRIVATE Qt6::Quick
    Qt6::QuickControls2
    Qt6::Network
    Qt6::Charts
    BuildConfig
)

include_directories(lib/include/)
include_directories(include/)
include_directories(include/data)
include_directories(include/models)

include(GNUInstallDirs)
install(TARGETS ${Pal_EXEC_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set_target_properties(${Pal_EXEC_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
)

if (ANDROID)
    set_target_properties(${Pal_EXEC_NAME} PROPERTIES
        QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/android
        COMPILE_DEFINITIONS "${COMPILE_DEFINITIONS} MOBILE")

    include(FetchContent)
    FetchContent_Declare(
        android_openssl
        DOWNLOAD_EXTRACT_TIMESTAMP true
        URL https://github.com/KDAB/android_openssl/archive/refs/heads/master.zip)

    FetchContent_MakeAvailable(android_openssl)
    include(${android_openssl_SOURCE_DIR}/android_openssl.cmake)

    add_android_openssl_libraries(${Pal_EXEC_NAME})
endif()

if(UNIX AND APPLE)
    # Mac bundle settings
    set(MACOSX_BUNDLE_BUNDLE_NAME "${Pal_APP_NAME}")
    set(MACOSX_BUNDLE_INFO_STRING "${Pal_APP_NAME}: An offline, QR-Based scouter for FRC use.")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.${Pal_ORG_NAME}.${Pal_APP_NAME}")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "${Pal_GIT_TAG_NUMERO}")
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${Pal_GIT_TAG_NUMERO}")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING "${Pal_GIT_TAG_NUMERO}")
    set(MACOSX_BUNDLE_ICON_FILE ${Pal_APP_NAME}.icns)
    set(MACOSX_BUNDLE_COPYRIGHT "Copyleft 2024 ${Pal_ORG_NAME}")

    # install as bundle
    set(INSTALL_BUNDLE "full")
endif()
