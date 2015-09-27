#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libparlex.la

#######################################
# Build information for each library

# Sources for libparlex
libparlex_la_SOURCES = builtins.cpp dfa.cpp job.cpp parser.cpp recognizer.cpp state_machine.cpp subjob.cpp terminal.cpp

# Linker options libTestProgram
libparlex_la_LDFLAGS = 

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libparlex_la_CPPFLAGS = -I$(top_srcdir)/include -std=c++11 -pthread

