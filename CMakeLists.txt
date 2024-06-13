cmake_minimum_required(VERSION 3.5)

project(OFP VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Widgets Network)

if (FORCE_QT6)
    set(QT_VERSION_MAJOR 6)
elseif (FORCE_QT5)
    set(QT_VERSION_MAJOR 5)
endif()

set(QT_VERSION_MAJOR 6)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Network)

# link_directories(/usr/local/lib)
# set(OFPLib_DIR "/usr/local/share/OFPLib/cmake")
find_package(OFPLib REQUIRED)

# set(CODE_SOURCES
#     main.cpp
#     src/dialogs/FoodSearch.cpp include/dialogs/FoodSearch.h

#     include/items/FoodInfoWidget.h src/items/FoodInfoWidget.cpp
#     include/MainWindow.h src/MainWindow.cpp

#     include/setup/SetupWizard.h src/setup/SetupWizard.cpp
#     include/setup/IntroPage.h src/setup/IntroPage.cpp
#     include/setup/GoalsPage.h src/setup/GoalsPage.cpp

#     include/pages/JournalPage.h src/pages/JournalPage.cpp

#     include/items/JournalItem.h src/items/JournalItem.cpp
# )

set(UI_ELEMENTS
    MainWindow

    setup/SetupWizard
    setup/IntroPage
    setup/GoalsPage

    pages/JournalPage

    items/MealLog
    items/FoodInfoWidget

    dialogs/FoodServingEdit
    dialogs/FoodSearch
)

set(CODE_ELEMENTS

)

foreach(ELEMENT ${UI_ELEMENTS})
    set(HEADERS ${HEADERS} include/${ELEMENT}.h)
    set(SOURCES ${SOURCES} src/${ELEMENT}.cpp)
    set(UI ${UI} ui/${ELEMENT}.ui)
endforeach()

foreach(ELEMENT ${CODE_ELEMENTS})
    set(HEADERS ${HEADERS} include/${ELEMENT}.h)
    set(SOURCES ${SOURCES} src/${ELEMENT}.cpp)
endforeach()

# set(UI_SOURCES
#     ui/items/FoodInfoWidget.ui
#     ui/MainWindow.ui

#     ui/setup/SetupWizard.ui
#     ui/setup/IntroPage.ui
#     ui/setup/GoalsPage.ui

#     ui/pages/JournalPage.ui

#     ui/items/JournalItem.ui

#     ui/dialogs/FoodSearch.ui
# )

# set(SOURCES
#     ${UI_SOURCES}
#     ${CODE_SOURCES}
# )
set(PROJECT_SOURCES
    main.cpp
    ${UI}
    ${HEADERS}
    ${SOURCES}
)

qt_wrap_ui(SOURCES ${UI})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(OFP
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET OFP APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(OFP SHARED
            ${PROJECT_SOURCES}
        )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
else()
    add_executable(OFP
        ${PROJECT_SOURCES}
    )
endif()
endif()

target_link_libraries(OFP PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network ofp)
target_include_directories(OFP PRIVATE include/)
# target_include_directories(OFP PRIVATE /usr/local/include)
# target_include_directories(OFP PRIVATE include/setup)
target_include_directories(OFP PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.OFP)
endif()
set_target_properties(OFP PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS OFP
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(OFP)
endif()
