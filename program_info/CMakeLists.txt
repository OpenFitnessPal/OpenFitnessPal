# Config stuff
if(UNIX AND NOT(APPLE))
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${OFP_APP_NAME}.desktop DESTINATION "share/applications")
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${OFP_APP_NAME}.svg DESTINATION "share/icons/hicolor/scalable/apps")
    #install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${OFP_APP_NAME}-symbolic.svg DESTINATION "share/icons/hicolor/symbolic/apps" RENAME ${OFP_APP_NAME}.svg)
endif()

set(OFP_VERSION_WIN ${OFP_VERSION_MAJOR}.${OFP_VERSION_MINOR}.${OFP_VERSION_HOTFIX}.0)

configure_file(${OFP_APP_NAME}.rc.in ${OFP_APP_NAME}.rc @ONLY)
configure_file(${OFP_APP_NAME}.manifest.in ${OFP_APP_NAME}.manifest @ONLY)
configure_file(${OFP_APP_NAME}.desktop.in ${OFP_APP_NAME}.desktop)
configure_file(${OFP_APP_NAME}.ico ${OFP_APP_NAME}.ico COPYONLY)
#configure_file(win_install.nsi.in win_install.nsi @ONLY)
#configure_file(${OFP_APP_NAME}.icns ${OFP_APP_NAME}.icns COPYONLY)
