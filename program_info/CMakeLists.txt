# Config stuff
if(UNIX AND NOT(APPLE))
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/OpenFitnessPal.desktop DESTINATION "share/applications")
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/OpenFitnessPal.svg DESTINATION "share/icons/hicolor/scalable/apps")
    #install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/OpenFitnessPal-symbolic.svg DESTINATION "share/icons/hicolor/symbolic/apps" RENAME OpenFitnessPal.svg)
endif()

#set(Dashboard_VERSION_WIN ${Dashboard_VERSION_MAJOR}.${Dashboard_VERSION_MINOR}.${Dashboard_VERSION_HOTFIX}.0)

#configure_file(OpenFitnessPal.rc.in OpenFitnessPal.rc @ONLY)
#configure_file(OpenFitnessPal.manifest.in OpenFitnessPal.manifest @ONLY)
configure_file(OpenFitnessPal.desktop.in OpenFitnessPal.desktop)
#configure_file(OpenFitnessPal.ico OpenFitnessPal.ico COPYONLY)
#configure_file(win_install.nsi.in win_install.nsi @ONLY)
#configure_file(OpenFitnessPal.icns OpenFitnessPal.icns COPYONLY)
