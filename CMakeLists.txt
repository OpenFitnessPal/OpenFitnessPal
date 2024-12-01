cmake_minimum_required(VERSION 3.16)

set(OFP_APP_NAME OpenFitnessPal)
set(OFP_EXEC_NAME OFP)
set(OFP_ORG_NAME OpenFitnessPal)
set(OFP_GIT_REPO https://github.com/${OFP_ORG_NAME}/${OFP_APP_NAME})

project(OpenFitnessPal VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Quick)
add_subdirectory(3rd_party EXCLUDE_FROM_ALL)

qt_standard_project_setup(REQUIRES 6.7)

if(WIN32)
    set(RCS_FILE ${CMAKE_CURRENT_BINARY_DIR}/program_info/${OFP_APP_NAME}.rc)
    set(OFP_BUILD_PLATFORM "win32")
elseif(ANDROID)
    set(ANDROID_GUI ON)
    set(MANIFEST_FILE android/AndroidManifest.xml)
    set(OFP_BUILD_PLATFORM "an64")
elseif(APPLE)
    set(OFP_BUILD_PLATFORM "mac64")
else()
    set(OFP_BUILD_PLATFORM "lin64")
endif()

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

project(OpenFitnessPal VERSION ${OFP_GIT_TAG_NUMERO} LANGUAGES CXX)

# Build Date
string(TIMESTAMP TODAY "%Y-%m-%d")
set(OFP_BUILD_TIMESTAMP "${TODAY}")

add_subdirectory("program_info")
find_package(OFPLib)

set(QRC_FILES icons.qrc)

qt_add_executable(${OFP_EXEC_NAME}
    src/main.cpp
    ${QRC_FILES}
    ${RCS_FILE}
    ${MANIFEST_FILE}

    ${OFPLib_SOURCE_DIR}/include/OFPManager.h
    ${OFPLib_SOURCE_DIR}/include/FoodItem.h
    ${OFPLib_SOURCE_DIR}/include/ServingSize.h
    ${OFPLib_SOURCE_DIR}/include/NutrientUnion.h

    ${CMAKE_BINARY_DIR}/buildconfig/BuildConfig.cpp
)

set_target_properties(${OFP_EXEC_NAME} PROPERTIES OUTPUT_NAME ${OFP_APP_NAME})

if (ANDROID)
    include(FetchContent)
    FetchContent_Declare(
        android_openssl
        DOWNLOAD_EXTRACT_TIMESTAMP true
        URL https://github.com/KDAB/android_openssl/archive/refs/heads/master.zip)

    FetchContent_MakeAvailable(android_openssl)
    include(${android_openssl_SOURCE_DIR}/android_openssl.cmake)

    add_android_openssl_libraries(${OFP_EXEC_NAME})

    set_target_properties(${OFP_EXEC_NAME} PROPERTIES
        QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/android
        COMPILE_DEFINITIONS "${COMPILE_DEFINITIONS} MOBILE")
endif()

qt_add_resources(${OFP_EXEC_NAME} "configuration"
    PREFIX "/"
    FILES
    qtquickcontrols2.conf)

set_source_files_properties(qml/Constants.qml
    PROPERTIES
    QT_QML_SINGLETON_TYPE true
)

set(ELEMENTS
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

set(QML_ELEMENTS
    App
    DateSelect
    RemoveButton.ui
    Constants
    AddButton.ui
    DoubleSpinBox
    LabeledTextField

    goals/IntGoalForm.ui
    goals/IntGoal
    goals/MacroGoals
    goals/GoalsPageForm.ui
    goals/SuffixedSpinBox
    goals/GoalsPage
    goals/MacroGoalsForm.ui
    goals/WeightGoal
    goals/GoalSpinBox

    exercise/ExerciseRootPage
    exercise/ExerciseRootPageForm.ui

    exercise/routines/RoutinesPage
    exercise/routines/ExerciseRoutineEdit
    exercise/routines/ExerciseRoutineImpl
    exercise/routines/ExerciseRoutineEditForm.ui
    exercise/routines/RoutinesPageForm.ui
    exercise/routines/ExerciseRoutineForm.ui

    exercise/list/ExercisePage
    exercise/list/ExerciseSetImpl
    exercise/list/ExerciseSetForm.ui
    exercise/list/ExerciseForm.ui
    exercise/list/ExercisePageForm.ui
    exercise/list/ExerciseImpl

    food/FoodServingInfoForm.ui
    food/FoodSearchForm.ui
    food/JournalPageForm.ui
    food/FoodServingEditForm.ui
    food/JournalPage
    food/FoodServingInfo
    food/FoodServingEdit
    food/MealLogForm.ui
    food/FoodPageForm.ui
    food/FoodSearch
    food/FoodPage
    food/MealLog

    food/nutritionInfo/NutritionInfoHeaderForm.ui
    food/nutritionInfo/NutritionInfoHeader
    food/nutritionInfo/CaloriePreview
    food/nutritionInfo/NutritionInfo
    food/nutritionInfo/CaloriePreviewForm.ui
    food/nutritionInfo/NutritionInfoForm.ui
    food/nutritionInfo/NutritionGoalForm.ui
    food/nutritionInfo/NutritionGoal

    recipes/RecipeEditForm.ui
    recipes/RecipeAddForm.ui
    recipes/RecipeAdd
    recipes/RecipesPageForm.ui
    recipes/RecipeInfo
    recipes/RecipesPage
    recipes/RecipeInfoForm.ui
    recipes/RecipeEdit

    settings/SettingsPageRoot
    settings/DirSettingForm.ui
    settings/DirSetting
    settings/search/SearchSettingsPageForm.ui
    settings/search/NutrientFilterForm.ui
    settings/search/NutrientFilter
    settings/search/SearchSettingsPage
    settings/SettingsPage
    settings/SettingsPageRootForm.ui
    settings/MealNameSettingForm.ui
    settings/SettingsPageForm.ui
    settings/MealNameSetting
)

foreach(ELEMENT ${ELEMENTS})
    set(HEADERS ${HEADERS} include/${ELEMENT}.h)
    set(SOURCES ${SOURCES} src/${ELEMENT}.cpp)
endforeach()

foreach(QML ${QML_ELEMENTS})
    set(QML_FILES ${QML_FILES} qml/${QML}.qml)
endforeach()

add_subdirectory(buildconfig)

qt_add_qml_module(${OFP_EXEC_NAME}
    URI OpenFitnessPalContent
    VERSION 1.0
    QML_FILES ${QML_FILES}

    SOURCES ${SOURCES} ${HEADERS}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${OFP_EXEC_NAME} PROPERTIES
    #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${OFP_EXEC_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(${OFP_EXEC_NAME}
    PRIVATE Qt6::Quick
    BuildConfig
    OFPLib
)

target_include_directories(${OFP_EXEC_NAME} PRIVATE include/)
target_include_directories(${OFP_EXEC_NAME} PRIVATE include/items)
target_include_directories(${OFP_EXEC_NAME} PRIVATE include/data)
target_include_directories(${OFP_EXEC_NAME} PRIVATE include/models)
target_include_directories(${OFP_EXEC_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${OFP_EXEC_NAME} PRIVATE ${OFPLib_SOURCE_DIR}/include)

include(GNUInstallDirs)
install(TARGETS ${OFP_EXEC_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set_target_properties(${OFP_EXEC_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
)

if(UNIX AND APPLE)
    # Mac bundle settings
    set(MACOSX_BUNDLE_BUNDLE_NAME "${OFP_APP_NAME}")
    set(MACOSX_BUNDLE_INFO_STRING "${OFP_APP_NAME}: A free, open-source fitness tracker.")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.${OFP_ORG_NAME}.${OFP_APP_NAME}")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "${OFP_GIT_TAG_NUMERO}")
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${OFP_GIT_TAG_NUMERO}")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING "${OFP_GIT_TAG_NUMERO}")
    set(MACOSX_BUNDLE_ICON_FILE ${OFP_APP_NAME}.icns)
    set(MACOSX_BUNDLE_COPYRIGHT "Copyleft 2024 ${OFP_ORG_NAME}")

    # install as bundle
    set(INSTALL_BUNDLE "full")
endif()
