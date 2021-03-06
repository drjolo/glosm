# Depends
FIND_PACKAGE(Threads REQUIRED)

# Checks
IF(NOT CMAKE_CROSSCOMPILING)
	INCLUDE(CheckFunctionExists)
	SET(CMAKE_EXTRA_INCLUDE_FILES "math.h")
	SET(CMAKE_REQUIRED_LIBRARIES m)
	CHECK_FUNCTION_EXISTS(sincos HAVE_SINCOS)
	SET(CMAKE_REQUIRED_LIBRARIES)
	SET(CMAKE_EXTRA_INCLUDE_FILES)
ENDIF(NOT CMAKE_CROSSCOMPILING)

IF(HAVE_SINCOS)
	ADD_DEFINITIONS(-DHAVE_SINCOS)
ENDIF(HAVE_SINCOS)

# Targets
SET(SOURCES
	src/CheckGL.cc
	src/FirstPersonViewer.cc
	src/GPXLayer.cc
	src/GPXTile.cc
	src/GeometryLayer.cc
	src/GeometryTile.cc
	src/MercatorProjection.cc
	src/OrthoViewer.cc
	src/Projection.cc
	src/SphericalProjection.cc
	src/TerrainLayer.cc
	src/TerrainTile.cc
	src/TileManager.cc
	src/mglu.cc
)

# We check whether GL functions != NULL there. These funcions may
# really be either function pointers (which are perfectly OK to
# compare with NULL) or normal functions (for which warning will
# be generated, while comparison still gives correct result).
# We have to ignore the warning because there can be mix of both
SET_SOURCE_FILES_PROPERTIES(
	src/CheckGL.cc
	PROPERTIES
	COMPILE_FLAGS "-Wno-address"
)

SET(HEADERS
)

INCLUDE_DIRECTORIES(include ../libglosm-server/include ${EXPAT_INCLUDE_DIR} ${GL_INCLUDE_DIRS})

ADD_LIBRARY(glosm-client SHARED ${SOURCES})
TARGET_LINK_LIBRARIES(glosm-client glosm-server ${GL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# Installation
# We don't have even a sight of stable API, so don't use soversion
# and don't install headers yet. May be enabled if there are any
# third party users of libglosm
#SET_TARGET_PROPERTIES(glosmclient PROPERTIES SOVERSION 1)
#INSTALL(FILES ${HEADERS} DESTINATION include/glosm)

IF(NOT CMAKE_CROSSCOMPILING)
	INSTALL(TARGETS glosm-client LIBRARY DESTINATION ${LIBDIR})
ENDIF(NOT CMAKE_CROSSCOMPILING)
