################################################################################
#
# Description:
#	Configuration of paths for templates
#
# Authors:
#	Milan Vukov, milan.vukov@esat.kuleuven.be
# 	Rien Quirynen
#
# Year:
#	2011 - 2013
#
#
################################################################################

#
# Template paths
#

SET( INSTALL_TEMPLATE_PATH
	${INSTALL_INCLUDE_DIR}/acado/code_generation/templates
)

SET( TEMPLATE_PATHS ${CMAKE_CURRENT_SOURCE_DIR} ${INSTALL_TEMPLATE_PATH} )

#
# Templates
#

SET( INTEGRATOR_MEX_TEMPLATE integrator_mex.c.in)
SET( RHS_MEX_TEMPLATE rhs_mex.c.in)

SET( FORCES_TEMPLATE forces_interface.in)
SET( FORCES_GENERATOR acado_forces_generator.m.in)
SET( QPOASES_HEADER qpoases_interface.hpp.in)
SET( QPOASES_SOURCE qpoases_interface.cpp.in)
SET( QPDUNES_TEMPLATE qpdunes_interface.in)

SET( AUXILIARY_FUNCTIONS_HEADER acado_auxiliary_functions.h.in)
SET( AUXILIARY_FUNCTIONS_SOURCE acado_auxiliary_functions.c.in)
SET( AUXILIARY_SIM_FUNCTIONS_HEADER acado_auxiliary_sim_functions.h.in)
SET( AUXILIARY_SIM_FUNCTIONS_SOURCE acado_auxiliary_sim_functions.c.in)
SET( SOLVER_MEX acado_solver_mex.c.in)
SET( MAKE_MEX_FORCES make_acado_solver_forces.m.in)
SET( MAKE_MEX_QPOASES make_acado_solver_qpoases.m.in)
SET( MAKE_MEX_INTEGRATOR make_acado_integrator.m.in)
SET( MAKE_MEX_MODEL make_acado_model.m.in)
SET( MAKEFILE_FORCES makefile.forces.in)
SET( MAKEFILE_QPOASES makefile.qpoases.in)
SET( MAKEFILE_INTEGRATOR makefile.integrator.in)

SET( MAKEFILE_SFUN_QPOASES make_acado_solver_sfunction.m.in)
SET( SOLVER_SFUN_SOURCE acado_solver_sfunction.c.in)
SET( SOLVER_SFUN_HEADER acado_solver_sfunction.h.in)

SET( DUMMY_TEST_FILE dummy_test_file.in)

SET( COMMON_HEADER_TEMPLATE acado_common_header.h.in)

#
# Configure templates
#

SET( CG_TEMPLATES_PATH
	${PROJECT_BINARY_DIR}/include/acado/code_generation/templates
)

CONFIGURE_FILE(
	"${CMAKE_CURRENT_SOURCE_DIR}/templates.hpp.in"
	"${CG_TEMPLATES_PATH}/templates.hpp"
	@ONLY
)

#
# Install templates
#

FILE( GLOB TMP ./*.in )

INSTALL(
	FILES
		"${CG_TEMPLATES_PATH}/templates.hpp"
		${TMP}
	DESTINATION
		${INSTALL_INCLUDE_DIR}/acado/code_generation/templates
)
