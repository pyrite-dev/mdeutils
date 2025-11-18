project(
	mbiff
)

file(
	GLOB
	mbiff_SRC
	*.c
)

add_executable(
	mbiff
	${mbiff_SRC}
)

target_link_libraries(
	mbiff
	PRIVATE
	MDELib Mw
)

include(GNUInstallDirs)
install(
	TARGETS mbiff
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
