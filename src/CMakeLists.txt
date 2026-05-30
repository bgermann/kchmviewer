INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR}/src )

# Project files
SET( kchmviewerSources 
	config.cpp
	dbus_interface.cpp
	dialog_chooseurlfromlist.cpp
	dialog_setup.cpp
	kde-qt.cpp
	main.cpp
	mainwindow.cpp
	recentfiles.cpp
	settings.cpp
	tab_bookmarks.cpp
	tab_contents.cpp
	tab_index.cpp
	tab_search.cpp
	viewwindowmgr.cpp
	navigationpanel.cpp
	checknewversion.cpp
	toolbarmanager.cpp
	toolbareditor.cpp
	textencodings.cpp
	treeitem_toc.cpp
	treeitem_index.cpp
	viewwindow_webengine.cpp
	dataprovider_qwebengine.cpp
	resources/images.qrc
  )

add_executable( kchmviewer ${kchmviewerSources} )

target_link_libraries( kchmviewer
	ebook
	${LIBCHM_LIBRARY}
	${LIBZIP_LIBRARY}
	Qt6::Core
	Qt6::Widgets
	Qt6::Network
	Qt6::PrintSupport
	Qt6::DBus
	Qt6::WebEngineWidgets
	Qt6::Xml
)

if(KF6_FOUND)
	target_link_libraries( kchmviewer KF6::I18n KF6::WidgetsAddons )
elseif(KF5_FOUND)
	target_link_libraries( kchmviewer KF5::I18n KF5::WidgetsAddons )
endif()

INSTALL( TARGETS kchmviewer DESTINATION bin )

