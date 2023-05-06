#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

PROJECTNAME := yash
WINCOMP		:= x86_64-w64-mingw32-g++

# define the C++ compiler to use
CXX = g++

# define any compile-time flags
CXXFLAGS	:= -std=c++23 -g -I"C:\Program Files\boost\boost_1_82_0" -L"C:\Program Files\boost\boost_1_82_0\stage\lib"



#  -Wall -Wextra

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = 


# define output directory
OUTPUT	:= bin

# define source directory
SRC		:= src

# define include directory
INCLUDE	:= include

# define lib directory
LIB		:= lib

ifeq ($(OS),Windows_NT)
MAIN	:= $(PROJECTNAME).exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
FIXPATH = $(subst /,\,$1)
RM			:= del /q /f
MD	:= mkdir
else
MAIN	:= $(PROJECTNAME)
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p
endif

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

# define the C libs
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

# define the C source files
SOURCES		:= $(wildcard $(patsubst %,%/*.cc, $(SOURCEDIRS)))

# define the C object files 
OBJECTS		:= $(SOURCES:.cc=.o)

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(MAIN))

all: $(OUTPUT) $(MAIN)
	@echo Executing 'all' complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

$(MAIN): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.cc.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@

.PHONY: clean
clean:
	$(RM) $(call FIXPATH,$(OBJECTS))
	@echo Cleanup complete!

cleanup:
	$(RM) $(call FIXPATH, $(SOURCES))
	@echo Successfully removed source files

recover:
	git pull

run: all
	./$(OUTPUTMAIN)
	@echo Executing 'run: all' complete!

install:
	make
	export PATH="$HOME/yash/bin:$PATH"

update:
	git pull && make

upgrade:
	git pull && make



