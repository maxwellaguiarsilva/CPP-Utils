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
	${OBJECTDIR}/_ext/d735dd4/cpp_utils.o \
	${OBJECTDIR}/_ext/d735dd4/game_utils.o \
	${OBJECTDIR}/source/automaton.o \
	${OBJECTDIR}/source/terminal_menu.o \
	${OBJECTDIR}/source/terminal_utils.o


# C Compiler Flags
CFLAGS=-m64

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=--64

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcpp-utils.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcpp-utils.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcpp-utils.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcpp-utils.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcpp-utils.a

${OBJECTDIR}/_ext/d735dd4/cpp_utils.o: /home/maxwell/NetBeansProjects/CPP-Utils/source/cpp_utils.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/d735dd4
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -Iinclude -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d735dd4/cpp_utils.o /home/maxwell/NetBeansProjects/CPP-Utils/source/cpp_utils.cpp

${OBJECTDIR}/_ext/d735dd4/game_utils.o: /home/maxwell/NetBeansProjects/CPP-Utils/source/game_utils.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/d735dd4
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -Iinclude -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d735dd4/game_utils.o /home/maxwell/NetBeansProjects/CPP-Utils/source/game_utils.cpp

${OBJECTDIR}/source/automaton.o: source/automaton.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -Iinclude -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/automaton.o source/automaton.cpp

${OBJECTDIR}/source/terminal_menu.o: source/terminal_menu.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -Iinclude -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/terminal_menu.o source/terminal_menu.cpp

${OBJECTDIR}/source/terminal_utils.o: source/terminal_utils.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -Iinclude -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/terminal_utils.o source/terminal_utils.cpp

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
