set(ktagebuch_SRCS
   ktagebuch.cpp
   main.cpp
   ktagebuchview.cpp
   fs/filesystem.cpp
   library/ui/datepickerdlg.cpp   
   library/ui/finddialog.cpp
 )

add_subdirectory( fs )

kde4_add_ui_files(ktagebuch_SRCS prefs_base.ui prefs_colors.ui prefs_font.ui)

kde4_add_kcfg_files(ktagebuch_SRCS settings.kcfgc )

kde4_add_executable(ktagebuch ${ktagebuch_SRCS})

target_link_libraries(ktagebuch ${KDE4_KDEUI_LIBS} ${SQLITE_LIBRARIES} )

install(TARGETS ktagebuch ${INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( FILES ktagebuch.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES ktagebuch.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES ktagebuchui.rc  DESTINATION  ${DATA_INSTALL_DIR}/ktagebuch )
