# Config stuff
if(UNIX AND NOT(APPLE))
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${Pal_APP_NAME}.desktop DESTINATION "share/applications")
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${Pal_APP_NAME}.svg DESTINATION "share/icons/hicolor/scalable/apps")
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${Pal_APP_NAME}-symbolic.svg DESTINATION "share/icons/hicolor/symbolic/apps" RENAME ${Pal_APP_NAME}.svg)
endif()

set(Pal_VERSION_WIN ${Pal_VERSION_MAJOR}.${Pal_VERSION_MINOR}.${Pal_VERSION_HOTFIX}.0)

configure_file(${Pal_APP_NAME}.rc.in ${Pal_APP_NAME}.rc @ONLY)
configure_file(${Pal_APP_NAME}.manifest.in ${Pal_APP_NAME}.manifest @ONLY)
configure_file(${Pal_APP_NAME}.desktop.in ${Pal_APP_NAME}.desktop)
configure_file(${Pal_APP_NAME}.ico ${Pal_APP_NAME}.ico COPYONLY)
configure_file(${Pal_APP_NAME}.svg ${Pal_APP_NAME}.svg COPYONLY)
configure_file(win_install.nsi.in win_install.nsi @ONLY)
configure_file(${Pal_APP_NAME}.icns ${Pal_APP_NAME}.icns COPYONLY)
