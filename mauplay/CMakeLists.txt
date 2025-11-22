include(MDEBase)
include(MDEPkgConfig)
setup_project(mauplay ${CMAKE_INSTALL_BINDIR})

pkg_config_add(mauplay sqlite3)

target_link_libraries(
	mauplay
	PRIVATE
	MDEAudio
)

find_package(PkgConfig)
