include(MDEBase)
include(MDEOpenGL)
mde_setup_project(mcompass ${CMAKE_INSTALL_BINDIR})

mde_opengl_add(mcompass)
mde_math_add(mcompass)
