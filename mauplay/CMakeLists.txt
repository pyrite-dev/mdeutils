include(MDEBase)
include(MDEPkgConfig)
setup_project(mauplay ${CMAKE_INSTALL_BINDIR})

pkg_config_add(mauplay sqlite3)
pkg_config_add(mauplay samplerate)
pkg_config_add(mauplay inih)

target_link_libraries(
	mauplay
	PRIVATE
	MDEAudio MDESound
)

if(NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_link_libraries(
		mauplay
		PRIVATE
		m
	)
endif()
