include(MDEBase)
include(MDEOpenGL)
mde_setup_project(mclock ${CMAKE_INSTALL_BINDIR})

mde_opengl_add(mclock)
mde_math_add(mclock)
