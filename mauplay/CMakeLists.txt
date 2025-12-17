include(MDEBase)
include(MDEPkgConfig)
mde_setup_project(mauplay ${CMAKE_INSTALL_BINDIR})

mde_pkg_config_add(mauplay sqlite3)
mde_pkg_config_add(mauplay samplerate)
mde_pkg_config_add(mauplay inih)
mde_math_add(mauplay)

target_link_libraries(
	mauplay
	PRIVATE
	MDEAudio MDESound
)
