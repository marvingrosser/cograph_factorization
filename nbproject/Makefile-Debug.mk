#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/classes/InputHandler.o \
	${OBJECTDIR}/src/classes/cograph.o \
	${OBJECTDIR}/src/classes/cotree.o \
	${OBJECTDIR}/src/classes/edge.o \
	${OBJECTDIR}/src/classes/main.o \
	${OBJECTDIR}/src/classes/reader.o \
	${OBJECTDIR}/src/classes/vertice.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-fopenmp
CXXFLAGS=-fopenmp

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cograph_factorization

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cograph_factorization: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cograph_factorization ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/classes/InputHandler.o: src/classes/InputHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/src/classes
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/classes/InputHandler.o src/classes/InputHandler.cpp

${OBJECTDIR}/src/classes/cograph.o: src/classes/cograph.cpp
	${MKDIR} -p ${OBJECTDIR}/src/classes
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/classes/cograph.o src/classes/cograph.cpp

${OBJECTDIR}/src/classes/cotree.o: src/classes/cotree.cpp
	${MKDIR} -p ${OBJECTDIR}/src/classes
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/classes/cotree.o src/classes/cotree.cpp

${OBJECTDIR}/src/classes/edge.o: src/classes/edge.cpp
	${MKDIR} -p ${OBJECTDIR}/src/classes
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/classes/edge.o src/classes/edge.cpp

${OBJECTDIR}/src/classes/main.o: src/classes/main.cpp
	${MKDIR} -p ${OBJECTDIR}/src/classes
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/classes/main.o src/classes/main.cpp

${OBJECTDIR}/src/classes/reader.o: src/classes/reader.cpp
	${MKDIR} -p ${OBJECTDIR}/src/classes
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/classes/reader.o src/classes/reader.cpp

${OBJECTDIR}/src/classes/vertice.o: src/classes/vertice.cpp
	${MKDIR} -p ${OBJECTDIR}/src/classes
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/classes/vertice.o src/classes/vertice.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
