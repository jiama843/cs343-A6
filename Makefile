OUTPUT:=OUTPUT

CXX = u++					# compiler
CXXFLAGS = -g -multi -O2 -std=c++11 -Wall -Wextra -MMD -D${OUTPUT} # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = printer.o # list of object files for question 1 prefixed with "q1"
EXEC = soda

DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"

#############################################################

.PHONY : all clean

all : ${EXEC}					# build all executables

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d ${OBJECTS} ${EXEC} LockImpl
